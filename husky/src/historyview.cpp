#include <QtGui>
#include "historyview.h"

/**
 * Class constructor.
 * @param	pParent	The parent widget
 * @param	szName	The widget's name
 */
HistoryView::HistoryView(QWidget* pParent) :
	QueryView(pParent)
{
	// Disable sorting
    setSortingEnabled(false);
	
    header()->setResizeMode(QHeaderView::ResizeToContents);
}

/**
 * Class destructor.
 */
HistoryView::~HistoryView()
{
}

/**
 * Creates a new list item showing a history record.
 * @param	sFunc	The name of the function
 * @param	sFile	The file path
 * @param	sLine	The line number in the above file
 * @param	sText	The line's text
 */
void HistoryView::addRecord(const QString& sFunc, const QString& sFile,
	const QString& sLine, const QString& sText, QTreeWidgetItem*)
{
	HistoryItem* pItem;

    QStringList s;
    s << sFunc << sFile << sLine << sText;
	
	pItem = new HistoryItem(this, s);
    setCurrentItem(pItem);
}

/**
 * Moves to the previous item in the history, selecting it for display.
 * Note that this function move to the item which chronologically precedes
 * the current one, which, in list view terms, is the next item.
 */
void HistoryView::selectPrev()
{
	QTreeWidgetItem* pItem;

	// Get the current item
	pItem = currentItem();
	
	// Select the next item in the list
	if (pItem != NULL && itemAbove(pItem) != NULL) {  // TODO maybe itemBelow()
		pItem = itemAbove(pItem);
		select(pItem);
	}
}

/**
 * Moves to the next item in the history, selecting it for display.
 * Note that this function move to the item which chronologically succedes
 * the current one, which, in list view terms, is the previous item.
 */
void HistoryView::selectNext()
{
	QTreeWidgetItem* pItem;

	// Get the current item
	pItem = currentItem();
	
	// Select the previous item in the list
	if (pItem != NULL && itemBelow(pItem) != NULL) {
		pItem = itemBelow(pItem);
		select(pItem);
	}
}

/**
 * Deletes the item on which a popup-menu has been invoked.
 * This slot is connected to the remove() signal of the QueryResultsMenu
 * object.
 * @param	pItem	The item to remove
 */
void HistoryView::slotRemoveItem(QTreeWidgetItem* pItem)
{
	QTreeWidgetItem * pCurItem, * pNextItem;
    HistoryItem *p, *c;
	
	pCurItem = pItem;
	if ((pNextItem = itemBelow(pCurItem)) != NULL) {
        p = (HistoryItem *)pNextItem;
        c = (HistoryItem *)pCurItem;
		p->m_pPrevSibling = c->m_pPrevSibling;
    }
	
	delete pCurItem;
}

#include "historyview.moc"
