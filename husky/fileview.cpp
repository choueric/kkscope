#include <qpushbutton.h>
#include <qfileinfo.h>
#include <KUrl>
#include <QTabWidget>
#include <kfiledialog.h>
#include "fileview.h"
#include "filelist.h"
#include "kscopepixmaps.h"

/**
 * Class constructor.
 * @param	pParent	The parent widget
 * @param	szName	The widget's name
 * @param	fl		Widget creation flags
 */
FileView::FileView(QWidget* pParent) :
    QWidget(pParent),
	m_sRoot("")
{
    setupUi(this);
	
	// Set the tab widget icons
	m_pTabWidget->setTabIcon(0, GET_PIXMAP(TabFileList));
	m_pTabWidget->setTabIcon(1, GET_PIXMAP(TabFileTree));
	
	// Create a single column for the file tree
	// m_pFileTree->addColumn("");
	
	// Send the fileRequested() signal whenever a file is selected in either
	// the list or the tree
	connect(m_pFileList, SIGNAL(fileRequested(const QString&, uint)), this,
		SIGNAL(fileRequested(const QString&, uint)));
	connect(m_pFileTree, SIGNAL(doubleClicked(QTreeWidgetItem*)), 
		this, SLOT(slotTreeItemSelected()));
	connect(m_pFileTree, SIGNAL(returnPressed(QTreeWidgetItem*)), this, 
		SLOT(slotTreeItemSelected()));
}

/**
 * Class destructor.
 */
FileView::~FileView()
{
}

/**
 * Sets a new common root path to both the file list and the tree.
 * @param	sRoot	The full path of the new root
 */
void FileView::setRoot(const QString& sRoot)
{
	// Nothing to do if the given root is the same as the old one
	if (sRoot == m_sRoot)
		return;
	
	m_sRoot = sRoot;
	
	// TODO: Remove the current branch
	
	// Update the file list
	m_pFileList->setRoot(sRoot);
	
	// Nothing more to do for an empty root directory
	if (sRoot.isEmpty())
		return;
    m_pFileTree->setRootUrl(sRoot);
}

/**
 * Clears the contents of the file view and file tree.
 */
void FileView::clear()
{
	m_pFileList->clear();
	setRoot("");
} 

/**
 * Emits the fileRequested() signal when a file name is selected in the file 
 * tree. An item is selected by either double-clicking it or by hittin 
 * "ENTER" when it is highlighted.
 * This slot is connected to the doubleClicked() and returnPressed() signals
 * of the KFileTreeView object.
 * @param	pItem	The selected tree item
 */
	
void FileView::slotTreeItemSelected()
{
    KUrl url = m_pFileTree->currentUrl();
    QString path = url.toLocalFile();
    QFileInfo info(path);
	 
	if (!info.isDir())
		emit fileRequested(path, 0);
}

#include "fileview.moc"
