#include <QTextStream>
#include "treewidget.h"
#include "queryviewdriver.h"

/**
 * Class constructor.
 * @param	pParent	Parent widget
 * @param	szName	The name of the widget
 */
TreeWidget::TreeWidget(QWidget* pParent) :
	QueryView(pParent),
	m_nQueryType(CscopeFrontend::Called)
{
	setRootIsDecorated(true);
	
	// Create a driver object
	m_pDriver = new QueryViewDriver(this, this);
	
	// Query a tree item when it is expanded for the first time
	connect(this, SIGNAL(expanded(QTreeWidgetItem*)), this,
		SLOT(slotQueryItem(QTreeWidgetItem*)));
}

/**
 * Class destructor.
 */
TreeWidget::~TreeWidget()
{
}

/**
 * Determines the mode of the tree.
 * @param	mode	The new mode (@see Mode)
 */
void TreeWidget::setMode(Mode mode)
{
	m_nQueryType = (mode == Called) ? CscopeFrontend::Called :
		CscopeFrontend::Calling;
}

/**
 * Sets a new root item for the tree.
 * @param	sFunc	The name of the function to serve as root
 */
void TreeWidget::setRoot(const QString& sFunc)
{
	QTreeWidgetItem* pRoot;
	
	// Remove the current root, if any
	if ((pRoot = topLevelItem(0)) != NULL)
		delete pRoot;
	
	// Create a new root item
    QStringList l;
    l << sFunc;
	pRoot = new QTreeWidgetItem(this, l);
    pRoot->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
}

/**
 * Runs a query on the root item.
 */
void TreeWidget::queryRoot()
{
	QTreeWidgetItem* pRoot;
	
	if ((pRoot = topLevelItem(0)) != NULL)
		slotQueryItem(pRoot);
}

/**
 * Stores the tree contents in the given file.
 * @param	pFile	An open file to write to
 */
void TreeWidget::save(FILE* pFile)
{
	QTextStream str(pFile, QIODevice::WriteOnly);
	QTreeWidgetItem* pRoot;
	Encoder enc;
	
	if (m_nQueryType == CscopeFrontend::Called)
		str << "calltree {\n";
	else
		str << "callingtree {\n";

	// Write the tree to the file
	pRoot = topLevelItem(0);
	str << pRoot->text(0) << "\n";
	str << '{' << "\n";
	saveItems(pRoot->child(0), str, enc);
	str << '}' << "\n";
	str << '}' << "\n";
}

/**
 * Recursively writes tree items to a file.
 * Given an item, the method writes this item and all of its siblings.
 * Child items are written recursively.
 * @param	pItem	The first item to write
 * @param	str		An initialised text stream to use for writing
 * @param	enc		An encoder for free-text strings
 */
void TreeWidget::saveItems(QTreeWidgetItem* pItem, QTextStream& str, Encoder& enc)
{
	// Iterate over all items in this level
    int index = indexOfTopLevelItem(pItem);
	for (int i = index; pItem != NULL; pItem = topLevelItem(++i)) {
		// Write function parameters
		str << pItem->text(0) << " [ "
			<< "kscope_file=\"" << pItem->text(1) << "\", "
			<< "kscope_line=" << pItem->text(2) << ", "
			<< "kscope_text=\"" << enc.encode(pItem->text(3)) << "\""
			<< "]" << endl;
		
		// Write child items
		str << "{" << endl;
		saveItems(pItem->child(0), str, enc);
		str << "}" << endl;
	}
}

/**
 * Creates a new tree item showing a query result record.
 * @param	sFunc	The name of the function
 * @param	sFile	The file path
 * @param	sLine	The line number in the above file
 * @param	sText	The line's text
 * @param	pParent	The parent for the new item
 */
void TreeWidget::addRecord(const QString& sFunc, const QString& sFile,
	const QString& sLine, const QString& sText, QTreeWidgetItem* pParent)
{
	QTreeWidgetItem* pItem;
	
	pItem = new QueryViewItem(pParent, m_pLastItem, 2);
	pItem->setText(0, sFunc);
	pItem->setText(1, sFile);
	pItem->setText(2, sLine);
	pItem->setText(3, sText);
	
    pItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
	m_pLastItem = pItem;
}

/**
 * Called when a query running on the tree terminates.
 * If there were no results, the item becomes non-expandable.
 * NOTE: On top of its current behaviour, this function is required in order to
 * override the default behaviour, as specified by QueryView.
 * @param	nResults	Number of results
 * @param	pParent		The item for which the query was executed
 */
void TreeWidget::queryFinished(uint nResults, QTreeWidgetItem* pParent)
{
	if (nResults == 0) {
		pParent->setChildIndicatorPolicy(QTreeWidgetItem::DontShowIndicator);
    } else {
		pParent->setExpanded(true);
    }
}

/**
 * Runs a query on the given item, unless it was queried before.
 * This slot is connected to the expanded() signal of the list view.
 * @param	pItem	The item to query
 */
void TreeWidget::slotQueryItem(QTreeWidgetItem* pItem)
{
	// Do nothing if the item was already queried
	// An item has been queried if it has children or marked as non-expandable
	if (pItem->child(0) != NULL || pItem->childIndicatorPolicy() == QTreeWidgetItem::DontShowIndicator)
		return;
		
	// Run the query
	m_pDriver->query(m_nQueryType, pItem->text(0), true, pItem);
}

/**
 * Hides all descendant that do not meet the given search criteria.
 * This slot is connected to the search() signal of the QueryResultsMenu
 * object.
 * The search is incremental: only visible items are checked, so that a new
 * search goes over the results of the previous one.
 * @param	pParent	The parent item whose child are searched
 * @param	re		The pattern to search
 * @param	nCol	The list column to search in
 */
void TreeWidget::slotSearch(QTreeWidgetItem* pParent, const QRegExp& re, 
	int nCol)
{
	QTreeWidgetItem* pItem;
	
	// Get the first child
	if (pParent != NULL)
		pItem = pParent->child(0);
	else
		pItem = topLevelItem(0);
	
	// Iterate over all child items
	while (pItem != NULL) {
		// Filter visible items only
		if (!pItem->isHidden() && re.indexIn(pItem->text(nCol)) == -1)
			pItem->setHidden(true);
		
		// Search child items recursively
		slotSearch(pItem, re, nCol);
		
		pItem = topLevelItem(indexOfTopLevelItem(pItem) + 1);
	}
}

void TreeWidget::slotShowAll()
{
    qFatal("not implement this function\n");
}

/**
 * Makes all descendants of the given item visible.
 * This slot is connected to the showAll() signal of the QueryResultsMenu
 * object.
 */
void TreeWidget::slotShowAll(QTreeWidgetItem* pParent)
{
	QTreeWidgetItem* pItem;
	
	// Get the first child
	if (pParent != NULL)
		pItem = pParent->child(0);
	else
		pItem = topLevelItem(0);
	
	// Iterate over all child items
	while (pItem != NULL) {
		pItem->setHidden(false);
		
		// Show child items recursively
		slotShowAll(pItem);
			
		pItem = topLevelItem(indexOfTopLevelItem(pItem) + 1);
	}
}

#include "treewidget.moc"
