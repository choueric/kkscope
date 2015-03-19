#ifndef QUERYRESULTSMENU_H
#define QUERYRESULTSMENU_H

#include <QMenu>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <qregexp.h>

/**
 * Provides a popup-menu for list views containing query results.
 * The popup menu contains commands for copying field text out of items and
 * for removing items.
 * This class assumes a certain ordering of the list columns. If an owner
 * object uses a different configuration, it needs to call setColumns() after
 * constructing the object.
 * @author Elad Lahav
 */
class QueryResultsMenu : public QMenu
{
	Q_OBJECT
	
public:
    QueryResultsMenu(QWidget* pParent = 0, const char* szName = 0);
    ~QueryResultsMenu();
	
public slots:		
	void slotShow(QTreeWidgetItem*, const QPoint&, int nCol);
	
signals:
	/** 
	 * Indicates that the "View Source" menu item was selected. 
	 * @param	pItem	The item for which the menu was displayed
	 */
	void viewSource(QTreeWidgetItem* pItem);
	 
	/**
	 * Indicates that the "Find Definition" menu item was selected.
	 * @param	sFunc	The function to look for
	 */
	void findDef(const QString& sFunc);
	
	/** 
	 * Indicates that the "Copy [Column]" menu item was selected. 
	 * @param	pItem	The item for which the menu was displayed
	 * @param	nCol	The requested column
	 */
	void copy(QTreeWidgetItem* pItem, int nCol);
	
	/**
	 * Indicates that the "Filter..." menu item was selected.
	 * @param	nCol	The column in which to search
	 */
	void filter(int nCol);
	
	/**
	 * Indicates that the "Show All" menu item was selected.
	 */
	void showAll();
	
	/** 
	 * Indicates that the "Remove Item" menu item was selected. 
	 * @param	pItem	The item for which the menu was displayed
	 */
	void remove(QTreeWidgetItem* pItem);
	
private:
	/** Menu item IDs. */
	enum { ViewSource, FindDef, Copy, Filter, ShowAll, Remove };
		
	/** The item for which the popup menu is provided (cannot be NULL). */
	QTreeWidgetItem* m_pItem;
	
	/** The list column for which the query was invoked. */
	int m_nCol;
	
private slots:
	void slotViewSource();
	void slotFindDef();
	void slotCopy();
	void slotFilter();
	void slotRemove();
};

#endif
