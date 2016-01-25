#include <klocale.h>
#include "filelistwidget.h"
#include "kscope.h"
#include "kscopeconfig.h"

#define FILE_LIST_COL_NUM 3
#define FILE_LIST_TYPE_COL 0
#define FILE_LIST_NAME_COL 1
#define FILE_LIST_PATH_COL 2

/**
 * Class constructor.
 * @param	pParent	The parent widget
 * @param	szName	The widget's name
 */
FileListWidget::FileListWidget(QWidget* pParent) :
	SearchListView(FILE_LIST_NAME_COL, pParent),
	m_sRoot(qgetenv("HOME"))
{
    m_pModel = new StringListModel(FILE_LIST_COL_NUM, this);
    QStringList header;
    header << i18n("Type") << i18n("File") << i18n("Path");
    m_pModel->setHeader(header);

    m_pView->header()->setResizeMode(QHeaderView::ResizeToContents);
	m_pView->setAllColumnsShowFocus(true);
    setSourceModel(m_pModel);
	
	// Sort only when asked to by the user
	if (Config().getAutoSortFiles())
		m_pView->sortByColumn(FILE_LIST_NAME_COL, Qt::AscendingOrder);
	
	// Set colours and font
	applyPrefs();
}

/**
 * Class destructor.
 */
FileListWidget::~FileListWidget()
{
}

/**
 * Adds a single entry to the file list.
 * Implements the addItem() virtual method of the FileListTarget base
 * class. When a FileList object is given as a parameter to
 * ProjectManager::fillList(), this method is called for each file included
 * in the project. A new list item is created, containing the file's name and
 * path, and is added to the list.
 * @param	sFilePath	The full path of a source file
 */
void FileListWidget::addItem(const QString& sFilePath)
{
	QString sFileType, sFileName, sPath;
	int nTypePos;

    // Extract the file name
    sFileName = sFilePath.mid(sFilePath.lastIndexOf('/') + 1);
    // qDebug() << "FileListWidget addItem(): " << sFileName;

	// Get the file's extension (empty string for file names without an
	// extension)
	nTypePos = sFileName.lastIndexOf('.');
	if (nTypePos > -1)
		sFileType = sFileName.mid(nTypePos + 1);
	
	// If a root path has been set, use a $ sign instead of that part of the
	// path
	sPath = sFilePath;
	if (m_sRoot != "/")
		sPath.replace(m_sRoot, "$");
    sPath.truncate(sPath.lastIndexOf('/') + 1);
	
	// Create the list item
    QStringList strList;
    strList << sFileType << sFileName << sPath;
    m_pModel->addItem(strList);
}

/**
 * Searches the list for the given file path.
 * @param	sPath	The full path of the file to find
 * @return	true if the file was found in the list, false otherwise
 */
bool FileListWidget::findFile(const QString& sPath)
{
	QString sFindPath(sPath);
    QList<QStandardItem *> list;
	
	if (m_sRoot != "/")
		sFindPath.replace(m_sRoot, "$");

	list = m_pModel->findItems(sFindPath, Qt::MatchExactly, FILE_LIST_PATH_COL);

	return !list.isEmpty();
}

/**
 * Removes all items from the file list.
 */
void FileListWidget::clear()
{
    m_pModel->removeRows(0, m_pModel->rowCount());
	m_pEdit->setText("");
}

/**
 * Opens a file for editing when its entry is clicked in the file list.
 * @param	pItem	The clicked list item
 */
void FileListWidget::processItemSelected(const QModelIndex &index)
{
    QString sFile;
	QString sPath;

    QModelIndex newIndex = m_proxyModel->index(index.row(), FILE_LIST_NAME_COL);
    sFile = m_proxyModel->data(newIndex).toString();

	// Get the file path (replace the root symbol, if required)
    newIndex = m_proxyModel->index(index.row(), FILE_LIST_PATH_COL);
	sPath = m_proxyModel->data(newIndex).toString();

	if (sPath.startsWith("$"))
		sPath.replace("$", m_sRoot);
    sPath += sFile;
	m_pEdit->setText("");

    if (sPath.isEmpty()) {
        qDebug() << __FUNCTION__ << "sPath is empty!";
        return;
    }
		
	// Submit a request to open the file for editing
	emit fileRequested(sPath, 0);
}

/**
 * Sets the list's colours and font, according the user's preferences.
 */
void FileListWidget::applyPrefs()
{
	m_proxyModel->setBgColor(Config().getColor(KScopeConfig::FileListBack));
	m_proxyModel->setFgColor(Config().getColor(KScopeConfig::FileListFore));
	m_pView->setFont(Config().getFont(KScopeConfig::FileList));
	m_pView->show();
}

/**
 * Associates a root directory with this list.
 * For each file in the list, the part of the path corresponding to the root
 * is replaced with a $ sign.
 * @param	sRoot	The new root path
 */
void FileListWidget::setRoot(const QString& sRoot)
{
	QString sPath;

    QStandardItem *pItem;

	// Update all items in the list
    for (int i = 0; i < m_pModel->rowCount(); i++) {
        pItem = m_pModel->item(i, FILE_LIST_PATH_COL);
        sPath = pItem->data().toString();
	
		// Restore the full path
		sPath.replace("$", m_sRoot);
		
		// Replace the root with a $ sign
		if (sRoot != "/")
			sPath.replace(sRoot, "$");
		
        sPath.truncate(sPath.lastIndexOf('/') + 1);
        pItem->setData(sPath);
	}
	
	// Store the new root
	m_sRoot = sRoot;
}

/**
 * Constructs a tool-tip for the given item.
 * @param	pItem	The item for which a tip is required
 * @param	sTip	The constructed tip string (on return)
 * @return	Always true
 */
bool FileListWidget::getTip(QModelIndex &index, QString &sTip)
{
    QModelIndex newIndex = m_proxyModel->index(index.row(), FILE_LIST_PATH_COL);
	sTip = m_proxyModel->data(newIndex).toString();
	return true;
}
