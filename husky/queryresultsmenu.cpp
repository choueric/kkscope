#include <klocale.h>
#include "queryresultsmenu.h"

/**
 * Class constructor.
 * @param	pParent	Parent widget
 * @param	szName	Optional object name
 */
QueryResultsMenu::QueryResultsMenu(QWidget* pParent, const char* szName) :
	QMenu(pParent),
	m_pItem(NULL)
{
	// Create the menu
	addAction(i18n("&View Source"), this, SLOT(slotViewSource()));
	addAction(i18n("Find &Definition"), this, SLOT(slotFindDef()));
	addSeparator();
	addAction(i18n("&Copy"), this, SLOT(slotCopy()));
	addSeparator();
	addAction(i18n("&Filter..."), this, SLOT(slotFilter()));
	addAction(i18n("&Show All"), this, SIGNAL(showAll()));
	addSeparator();
	addAction(i18n("&Remove Item"), this, SLOT(slotRemove()));
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
#if 0  //TODO
	// Save the requested item and column number to use in signals
	m_pItem = pItem;
	m_nCol = nCol;
	
	if (m_pItem == NULL) {
		// No item selected, disable everything but the "Filter" and "Show All" 
		// items
		setItemEnabled(ViewSource, false);
		setItemEnabled(FindDef, false);
		setItemEnabled(Copy, false);
		setItemEnabled(Remove, false);
	}
	else {
		// Item selected, enable record-specific actions
		setItemEnabled(ViewSource, true);
		setItemEnabled(Copy, true);
		setItemEnabled(Remove, true);
			
		// The "Find Definition" item should only be enabled if the mouse
		// was clicked over a valid function name 
		setItemEnabled(FindDef, (m_nCol == 0) && 
			(m_pItem->text(0) != "<global>"));

		// Set menu contents according to the column number
		switch (m_nCol) {
		case 0:
			changeItem(Copy, "&Copy Function");
			break;
			
		case 1:
			changeItem(Copy, "&Copy File");
			break;
			
		case 2:
			changeItem(Copy, "&Copy Line Number");
			break;
			
		case 3:
			changeItem(Copy, "&Copy Text");
			break;
			
		default:
			m_nCol = 0;
		}
	}
#endif
	
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

#include "queryresultsmenu.moc"
