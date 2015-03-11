#include <qlineedit.h>
#include <qfileinfo.h>
#include <klocale.h>
#include "filelist.h"

#include <QtDebug>

#ifndef TESTCASE
#include "kscope.h"
#include "kscopeconfig.h"
#endif

#define FILE_LIST_TYPE_COL 0
#define FILE_LIST_NAME_COL 1
#define FILE_LIST_PATH_COL 2
#define FILE_LIST_COL_NUM 3

/**
 * Class constructor.
 * @param	pParent	The parent widget
 * @param	szName	The widget's name
 */
FileList::FileList(QWidget* pParent, const char* szName) :
	SearchList(FILE_LIST_NAME_COL, pParent, szName),
	m_sRoot("/")
{
	// Set the list's columns
    m_pList->setColumnCount(FILE_LIST_COL_NUM);
    QStringList strList;
    strList << i18n("Type") << i18n("File") << i18n("Path");
    m_pList->setHeaderLabels(strList);
    m_pList->setRootIsDecorated(false);
	
#ifndef TESTCASE
	// Sort only when asked to by the user
	if (Config().getAutoSortFiles())
		m_pList->setSortColumn(FILE_LIST_NAME_COL);
	else
		m_pList->setSortColumn(m_pList->columns() + 1);
#else
    m_pList->setSortingEnabled(true);
#endif
	
	m_pList->setAllColumnsShowFocus(true);
	
	// Set colours and font
	applyPrefs();
}

/**
 * Class destructor.
 */
FileList::~FileList()
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
void FileList::addItem(const QString& sFilePath)
{
	QString sFileType, sFileName, sPath;
	int nTypePos;

    // Extract the file name
    sFileName = sFilePath.mid(sFilePath.lastIndexOf('/') + 1);
    qDebug() << sFileName;

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
	
	// Create the list item
    QStringList strList;
    strList << sFileType << sFileName << sPath;
	new QTreeWidgetItem(m_pList, strList);
}

/**
 * Searches the list for the given file path.
 * @param	sPath	The full path of the file to find
 * @return	true if the file was found in the list, false otherwise
 */
bool FileList::findFile(const QString& sPath)
{
	QString sFindPath(sPath);
    QList<QTreeWidgetItem *> list;
	
	if (m_sRoot != "/")
		sFindPath.replace(m_sRoot, "$");

	
	list = m_pList->findItems(sFindPath, Qt::MatchExactly, FILE_LIST_PATH_COL);

	return !list.isEmpty();
}

/**
 * Removes all items from the file list.
 */
void FileList::clear()
{
	m_pList->clear();
	m_pEdit->setText("");
}

/**
 * Opens a file for editing when its entry is clicked in the file list.
 * @param	pItem	The clicked list item
 */
void FileList::processItemSelected(QTreeWidgetItem* pItem)
{
	QString sPath;

	// Get the file path (replace the root symbol, if required)
	sPath = pItem->text(FILE_LIST_PATH_COL);
	if (sPath.startsWith("$"))
		sPath.replace("$", m_sRoot);
		
	// Submit a request to open the file for editing
	emit fileRequested(sPath, 0);
}

/**
 * Sets the list's colours and font, according the user's preferences.
 */
void FileList::applyPrefs()
{
    qDebug() << "TODO: " << __FUNCTION__;
#if 0
	// Apply colour settings
	m_pList->setPaletteBackgroundColor(Config().getColor(
		KScopeConfig::FileListBack));
	m_pList->setPaletteForegroundColor(Config().getColor(
		KScopeConfig::FileListFore));
	m_pList->setFont(Config().getFont(KScopeConfig::FileList));
#endif
}

/**
 * Associates a root directory with this list.
 * For each file in the list, the part of the path corresponding to the root
 * is replaced with a $ sign.
 * @param	sRoot	The new root path
 */
void FileList::setRoot(const QString& sRoot)
{
	QTreeWidgetItem* pItem;
    QTreeWidgetItemIterator it(m_pList);
	QString sPath;
	
	// Update all items in the list
    while (*it) {
        pItem = *it;
		sPath = pItem->text(FILE_LIST_PATH_COL);
		
		// Restore the full path
		sPath.replace("$", m_sRoot);
		
		// Replace the root with a $ sign
		if (sRoot != "/")
			sPath.replace(sRoot, "$");
		
		pItem->setText(FILE_LIST_PATH_COL, sPath);
        ++it;
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
bool FileList::getTip(QTreeWidgetItem* pItem, QString& sTip)
{
	sTip = pItem->text(FILE_LIST_PATH_COL);
	return true;
}

#include "filelist.moc"
