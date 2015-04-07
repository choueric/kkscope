#include <qpushbutton.h>
#include <qlineedit.h>
#include <kurlrequester.h>

#include "openprojectdlg.h"
#include "kscopeconfig.h"

/**
 * Class constructor.
 * @param	pParent	The parent widget
 * @param	szName	The widget's name
 */
OpenProjectDlg::OpenProjectDlg(QWidget* pParent)
{
    setupUi(this);
	loadRecent();
	m_pProjPathRequester->setFilter("cscope.proj");
}

/**
 * Class destructor.
 */
OpenProjectDlg::~OpenProjectDlg()
{
}

/**
 * @return	The selected project path
 */
QString OpenProjectDlg::getPath() const
{
	return m_pProjPathRequester->text();
}

/**
 * Sets the requester to reflect the selected project's directory, instead of
 * the cscope.proj file.
 * @param	sProjPath	The full path of the selected cscope.proj file
 */
void OpenProjectDlg::slotProjectSelected(const QString& sProjPath)
{
	QFileInfo fi(sProjPath);
	m_pProjPathRequester->setUrl(KUrl(fi.absolutePath()));
}

/**
 * Removes a project from the recent projects list.
 * This slot is connected to the clicked() signal of the "Remove" button.
 */
void OpenProjectDlg::slotRemoveRecent()
{
	QListWidgetItem* pItem;

	// Remove the selected item, if any
    QList<QListWidgetItem *> p = m_pRecentList->selectedItems();
	if (!p.isEmpty()) {
        pItem = m_pRecentList->currentItem();
		Config().removeRecentProject(pItem->text());
		m_pRecentList->removeItemWidget(pItem);
	}
}

/**
 * Selects a project for opening when an item is highlighted in the recent
 * projects list.
 * This slot is connected to the highlighted() signal of the recent projects
 * list box.
 * @param	pItem	The selected project item
 */
void OpenProjectDlg::slotSelectRecent(QListWidgetItem* pItem)
{
	if (pItem != NULL)
		m_pProjPathRequester->setUrl(KUrl(pItem->text()));
}

/**
 * Selects a project for opening and closes the dialogue when an item in the
 * recent projects list is double-clicked. 
 * This slot is connected to the doubleClicked() signal of the recent 
 * projects list box.
 * @param	pItem	The selected project item
 */
void OpenProjectDlg::slotOpenRecent(QListWidgetItem* pItem)
{
	if (pItem != NULL) {
		m_pProjPathRequester->setUrl(KUrl(pItem->text()));
		accept();
	}
}

/**
 * Fills the recent projects list box with the project paths read from the 
 * configuration file.
 */
void OpenProjectDlg::loadRecent()
{
	const QStringList& slProjects = Config().getRecentProjects();
	QStringList::const_iterator itr;

	// Create a list item for each project in the list
	for (itr = slProjects.begin(); itr != slProjects.end(); ++itr)
		m_pRecentList->addItem(*itr);
}

#include "openprojectdlg.moc"
