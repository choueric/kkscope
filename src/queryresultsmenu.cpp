#include <klocale.h>
#include "queryresultsmenu.h"

/**
 * Class constructor.
 * @param	pParent	Parent widget
 * @param	szName	Optional object name
 */
QueryResultsMenu::QueryResultsMenu(QWidget* pParent) :
	QMenu(pParent),
	m_pItem(NULL)
{
	// Create the menu
	m_pViewSourceAction = addAction(i18n("&View Source"), this, SLOT(slotViewSource()));
	m_pFindDefAction = addAction(i18n("Find &Definition"), this, SLOT(slotFindDef()));
	addSeparator();
	m_pCopyAction = addAction(i18n("&Copy"), this, SLOT(slotCopy()));
	addSeparator();
	m_pFilterAction = addAction(i18n("&Filter..."), this, SLOT(slotFilter()));
	m_pShowAllAction = addAction(i18n("&Show All"), this, SIGNAL(showAll()));
	addSeparator();
	m_pRemoveAction = addAction(i18n("&Remove Item"), this, SLOT(slotRemove()));
}

/**
 * Class destructor.
 */
QueryResultsMenu::~QueryResultsMenu()
{
}

/**
 * Displays the popup-menu at the requested coordinates.
 * @param	pItem	The item on which the menu was requested
 * @param	ptPos	The requested position for the menu
 * @param	nCol	The column over which the menu was requested, -1 if no
 *					column is associated with the request
 */
void QueryResultsMenu::slotShow(QTreeWidgetItem* pItem, const QPoint& ptPos, 
	int nCol)
{
	// Save the requested item and column number to use in signals
	m_pItem = pItem;
	m_nCol = nCol;
	
	if (m_pItem == NULL) {
		// No item selected, disable everything but the "Filter" and "Show All" 
        m_pViewSourceAction->setEnabled(false);
		m_pFindDefAction->setEnabled(false);
		m_pCopyAction->setEnabled(false);
		m_pRemoveAction->setEnabled(false);
	} else {
		// Item selected, enable record-specific actions
        m_pViewSourceAction->setEnabled(true);
		m_pCopyAction->setEnabled(true);
		m_pRemoveAction->setEnabled(true);
			
		// The "Find Definition" item should only be enabled if the mouse
		// was clicked over a valid function name 
        m_pFindDefAction->setEnabled((m_nCol == 0) && (m_pItem->text(0) != "<global>"));

		// Set menu contents according to the column number
		switch (m_nCol) {
		case 0:
			m_pCopyAction->setText("&Copy Function");
			break;
		case 1:
			m_pCopyAction->setText("&Copy File");
			break;
		case 2:
			m_pCopyAction->setText("&Copy Line Number");
			break;
		case 3:
			m_pCopyAction->setText("&Copy Text");
			break;
		default:
			m_nCol = 0;
		}
	}
	
	// Show the menu
	popup(ptPos);
}

/**
 * Emits the viewSource() signal.
 * This slot is activated when the "View Source" item is selected.
 */
void QueryResultsMenu::slotViewSource()
{
	if (m_pItem != NULL)
		emit viewSource(m_pItem);
}

/**
 * Emits the findDef() signal.
 * This slot is activated when the "Find Definition" item is selected.
 */
void QueryResultsMenu::slotFindDef()
{
	if (m_pItem != NULL)
		emit findDef(m_pItem->text(0));
}

/**
 * Emits the copy() signal.
 * This slot is activated when the "Copy [Column]" item is selected.
 */
void QueryResultsMenu::slotCopy()
{
	if (m_pItem != NULL)
		emit copy(m_pItem, m_nCol);
}

/**
 * Emits the filter() signal.
 * This slot is activated when the "Filter..." item is selected.
 */
void QueryResultsMenu::slotFilter()
{
	emit filter(m_nCol);
}

/**
 * Emits the remove() signal.
 * This slot is activated when the "Remove" item is selected.
 */
void QueryResultsMenu::slotRemove()
{
	if (m_pItem != NULL)
		emit remove(m_pItem);
} 
