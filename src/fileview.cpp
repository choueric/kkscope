#include "husky.h"
#include <qpushbutton.h>
#include <qfileinfo.h>
#include <KUrl>
#include <QTabWidget>
#include <kfiledialog.h>
#include "fileview.h"
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
	
    m_pFileModel = new QFileSystemModel;
    m_pFileModel->setRootPath(m_sRoot);
    m_pFileModel->setReadOnly(true);
    m_pFileTree->setModel(m_pFileModel);
    m_pFileTree->setRootIndex(m_pFileModel->index(m_sRoot));
	
	// Send the fileRequested() signal whenever a file is selected in either
	// the list or the tree
	connect(m_pFileList, SIGNAL(fileRequested(const QString&, uint)), this,
		SIGNAL(fileRequested(const QString&, uint)));
    // TODO: add returnEntered signal slot
	connect(m_pFileTree, SIGNAL(doubleClicked(const QModelIndex &)), 
		this, SLOT(slotTreeItemSelected(const QModelIndex &)));
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
    m_pFileModel->setRootPath(sRoot);
    m_pFileTree->setRootIndex(m_pFileModel->index(sRoot));
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
	
void FileView::slotTreeItemSelected(const QModelIndex & index)
{
    QFileInfo info = m_pFileModel->fileInfo(index);

    qDebug() << info.absoluteFilePath() << "is selected in FileTree";
	if (!info.isDir()) {
		emit fileRequested(info.absoluteFilePath(), 0);
    }
}
