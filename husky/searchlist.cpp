#include "husky.h"
#include <QKeyEvent>
#include <QApplication>
#include <QHeaderView>
#include <QTreeView>
#include "searchlist.h"

/**
 * Intercepting additional key events of QLineEdit to browse the list
 * @param	pKey	The pressed key event
 */
void SearchLineEdit::keyPressEvent(QKeyEvent* pKey) 
{
	switch(pKey->key()) {
	case Qt::Key_Up:
	case Qt::Key_Down:
	case Qt::Key_PageUp:
	case Qt::Key_PageDown:
		emit keyPressed(pKey); 
		break;
	
	default:
		QLineEdit::keyPressEvent(pKey);
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
 * Class constructor.
 * @param	nSearchCol	The list column on which to perform string look-ups
 * @param	pParent		The parent widget
 * @param	szName		The widget's name
 */
SearchList::SearchList(int nSearchCol, QWidget* pParent) :
    QWidget(pParent),
	m_nSearchCol(nSearchCol)
{
	// Create the child widgets
	m_pEdit = new SearchLineEdit(this);
	m_pList = new QTreeWidget(this);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_pEdit);
    layout->addWidget(m_pList);
    this->setLayout(layout);
	
	connect(m_pEdit, SIGNAL(textChanged(const QString&)), this,
		SLOT(slotFindItem(const QString&)));
	connect(m_pList, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), this,
		SLOT(slotItemSelected(QTreeWidgetItem *, int)));
#if 0 // TODO: add returnPressed slot
	connect(m_pList, SIGNAL(returnPressed(QTreeWidgetItem*)), this,
		SLOT(slotItemSelected(QTreeWidgetItem*)));
#endif
	connect(m_pEdit, SIGNAL(returnPressed()), this,
		SLOT(slotItemSelected()));
	connect(m_pEdit, SIGNAL(keyPressed(QKeyEvent*)), this,
		SLOT(slotKeyPressed(QKeyEvent*)));
}

/**
 * Class destructor.
 */
SearchList::~SearchList()
{
}

/**
 * Sets the keyboad focus to the search box.
 */
void SearchList::slotSetFocus()
{
	m_pEdit->setFocus();
}

/**
 * Selects a list item whose string begins with the text entered in the edit
 * widget.
 * This slot is connected to the textChanged() signal of the line edit widget.
 * @param	sText	The new text in the edit widget
 */
void SearchList::slotFindItem(const QString& sText)
{
	QList<QTreeWidgetItem *> items;
	
	// Try to find an item that contains this text
	// Priority to exactly matched, 
	// then try to find line begins with the text,
	// and if not found, then try to find the line contains the text
	items = m_pList->findItems(sText, 
            Qt::MatchExactly | Qt::MatchStartsWith| Qt::MatchContains);

	// Select this item
	if (!items.isEmpty()) {
		m_pList->setCurrentItem(items.first(), QItemSelectionModel::Select);
		m_pList->scrollToItem(items.first());
	}
}

/**
 * Lets inheriting classes process an item selection made through the list 
 * widget.
 * This slot is connected to the doubleClicked() and returnPressed()
 * signals of the list widget.
 */
void SearchList::slotItemSelected(QTreeWidgetItem *item, int column)
{
    qDebug() << "SearchList slot Item Selectd" << item->text(1);
	processItemSelected(item);
	m_pEdit->setText(item->text(1));
}

/**
 * Lets inheriting classes process an item selection made through the edit 
 * widget.
 * This slot is connected to the returnPressed() signal of the edit widget.
 */
void SearchList::slotItemSelected()
{
	QTreeWidgetItem* pItem;

	if ((pItem = m_pList->currentItem()) != NULL) {
		m_pEdit->setText(pItem->text(m_nSearchCol));
		processItemSelected(pItem);
	}
	
	m_pEdit->setText("");
}

#define SEARCH_MATCH(pItem) \
	pItem->text(m_nSearchCol).startsWith(m_pEdit->text())

/**
 * Sets a new current item based on key events in the edit box.
 * This slot is connected to the keyPressed() signal of the edit widget.
 * @param	pKey	The key evant passed by the edit box
 */
void SearchList::slotKeyPressed(QKeyEvent* pKey)
{
#if 1
    QApplication::sendEvent(m_pList, pKey);
#else
	QTreeWidgetItem* pItem, * pNewItem;
	int nPageSize, nPos;

	// Select the current item, or the first one if there is no current item
	pItem = m_pList->currentItem();
		
	// Set a new current item based on the pressed key
	switch (pKey->key()) {
	case  Qt::Key_Up:
        if (pItem) {
            for (pNewItem = m_pList->itemAbove(pItem);
                    pNewItem && !SEARCH_MATCH(pNewItem);
                    pNewItem = m_pList->itemAbove(pNewItem));
            if (pNewItem)
                pItem = pNewItem;
        }
		break;
		
	case  Qt::Key_Down:
        if (pItem) {
            for (pNewItem = m_pList->itemBelow(pItem);
                    pNewItem && !SEARCH_MATCH(pNewItem);
                    pNewItem = m_pList->itemBelow(pNewItem));
            if (pNewItem)
                pItem = pNewItem;
        }
		break;
	
	case  Qt::Key_PageUp:
		nPageSize = m_pList->visibleHeight() / pItem->height();
		for (nPos = 0; 
			pItem && pItem->itemAbove() && (nPos < nPageSize); 
			nPos++)
			pItem = pItem->itemAbove();
		break;
		
	case  Qt::Key_PageDown:
		nPageSize = m_pList->visibleHeight() / pItem->height();
		for (nPos = 0; 
			pItem && pItem->itemBelow() && (nPos < nPageSize); 
			nPos++)
			pItem = pItem->itemBelow();
		break;
	
	default:
		pKey->ignore();
		return;
	}

	// Select the first item if no other item was selected
	if (pItem == NULL)
		pItem = m_pList->topLevelItem(0);
		
	// Select the new item
	if (pItem) {
		m_pList->setCurrentItem(pItem);
		m_pList->scrollToItem(pItem);
	}
#endif
}

#include "searchlist.moc"
