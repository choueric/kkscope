#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include "queryview.h"
#include "encoder.h"

class QueryViewDriver;

/**
 * A tree-like widget displaying a hierarchical list of functions.
 * The widget has two modes: called functions and calling functions. Depending
 * on this mode, child items represent functions called by or calling their
 * parent item.
 * @author Elad Lahav
 */
class TreeWidget : public QueryView
{
	Q_OBJECT
	
public:
	TreeWidget(QWidget* pParent = 0);
	~TreeWidget();
	
	/**
	 * The type of tree to display.
	 */
	enum Mode { Called, Calling };
	
	void setMode(Mode);
	void setRoot(const QString&);
	void queryRoot();
	void save(FILE*);
	
	virtual void addRecord(const QString&, const QString&, const QString&,
		const QString&, QTreeWidgetItem*);
	virtual void queryFinished(uint, QTreeWidgetItem*);
	
protected slots:
	virtual void slotSearch(QTreeWidgetItem*, const QRegExp&, int);
	virtual void slotShowAll(QTreeWidgetItem*);
	
private:
	/** The CscopeFrontend query type to use (based on the current mode). */
	uint m_nQueryType;
	
	/** Runs queries and outputs the results as tree items. */
	QueryViewDriver* m_pDriver;
	
	void saveItems(QTreeWidgetItem*, QTextStream&, Encoder&);
	
private slots:
	void slotQueryItem(QTreeWidgetItem*);
};

#endif
