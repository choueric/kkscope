#include "searchlistview.h"

ListTreeView::ListTreeView(QWidget *parent) :
    QTreeView(parent)
{
}

ListTreeView::~ListTreeView()
{
}

/**
 * Handles double-click events over the view.
 * @param	pEvent	Event description object
 */
void ListTreeView::mouseDoubleClickEvent(QMouseEvent *pEvent)
{
	// Handle only left button double-clicks
	if (pEvent == NULL || pEvent->button() != Qt::LeftButton)
		return;
		
	// Find the clicked item
    QModelIndex index = indexAt(pEvent->pos());

	// Emit the doubleClicked() signal
	emit doubleClicked(index);
}

// to handle Return Press Event 
void ListTreeView::keyPressEvent(QKeyEvent *pEvent)
{
    if (pEvent->key() != Qt::Key_Return 
            && pEvent->key() != Qt::Key_Enter) {
        QTreeView::keyPressEvent(pEvent);
        return;
    }

    emit enterPressed(currentIndex());
}

////////////////////////////////////////////////////////////////////////////////

ListLineEdit::ListLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
}

ListLineEdit::~ListLineEdit()
{
}

// to handle up/down Press Event 
void ListLineEdit::keyPressEvent(QKeyEvent *pEvent)
{
    int is_up;

    if (pEvent->key() == Qt::Key_Up) {
        is_up = 1;
        emit upDownPressed(is_up);
    } else if (pEvent->key() == Qt::Key_Down) {
        is_up = 0;
        emit upDownPressed(is_up);
    } else
        QLineEdit::keyPressEvent(pEvent);
}

////////////////////////////////////////////////////////////////////////////////
ListSortFilterProxyModel::ListSortFilterProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent),
    m_bSortByInt(false),
    m_nSortCol(-1)
{
}

ListSortFilterProxyModel::~ListSortFilterProxyModel()
{
}

void ListSortFilterProxyModel::setSortByInt(int col, bool sortByInt)
{
    m_nSortCol = col;
    m_bSortByInt = sortByInt;
}
        
bool ListSortFilterProxyModel::lessThan(const QModelIndex &left, 
        const QModelIndex &right) const
{
    if (left.column() == m_nSortCol && m_bSortByInt) {
        uint iLeft = sourceModel()->data(left).toString().toUInt();
        uint iRight = sourceModel()->data(right).toString().toUInt();
        return iLeft < iRight;
    }
    return QSortFilterProxyModel::lessThan(left, right);
}

////////////////////////////////////////////////////////////////////////////////
SearchListView::SearchListView(int searchCol, QWidget *parent) :
    QWidget(parent),
    m_searchCol(searchCol)
{
    m_proxyModel = new ListSortFilterProxyModel;
    m_proxyModel->setFilterKeyColumn(m_searchCol);

    m_pView = new ListTreeView(this);
    m_pView->setRootIsDecorated(false);
    m_pView->setSortingEnabled(true);
    m_pView->setModel(m_proxyModel);
    m_pView->setSelectionMode(QAbstractItemView::SingleSelection);

    m_pEdit = new ListLineEdit(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_pEdit);
    layout->addWidget(m_pView);
    setLayout(layout);

    connect(m_pEdit, SIGNAL(textChanged(QString)),
            this, SLOT(slotFindItem()));

	connect(m_pView, SIGNAL(doubleClicked(const QModelIndex &)), 
            this, SLOT(slotItemSelected(const QModelIndex &)));

	connect(m_pView, SIGNAL(enterPressed(const QModelIndex &)),
            this, SLOT(slotViewEnterPressed(const QModelIndex &)));

	connect(m_pEdit, SIGNAL(returnPressed()), 
            this, SLOT(slotItemSelected()));

	connect(m_pEdit, SIGNAL(upDownPressed(int)), 
            this, SLOT(slotEditUpDownPressed(int)));
}
        
void SearchListView::setSourceModel(QAbstractItemModel *model)
{
    m_proxyModel->setSourceModel(model);
}

SearchListView::~SearchListView()
{
}

void SearchListView::slotFindItem()
{
    QRegExp regExp(m_pEdit->text(), Qt::CaseInsensitive);
    m_proxyModel->setFilterRegExp(regExp);
}

/**
 * Lets inheriting classes process an item selection made through the list 
 * widget.
 * This slot is connected to the doubleClicked() and returnPressed()
 */
void SearchListView::slotItemSelected(const QModelIndex &index)
{
	processItemSelected(index);
}

/**
 * Lets inheriting classes process an item selection made through the edit 
 * widget.
 * This slot is connected to the returnPressed() signal of the edit widget.
 */
void SearchListView::slotItemSelected()
{
    processItemSelected(m_pView->currentIndex());
	m_pEdit->setText("");
}

/**
 * Sets a new current item based on key events in the edit box.
 * This slot is connected to the keyPressed() signal of the edit widget.
 * @param	pKey	The key evant passed by the edit box
 */
void SearchListView::slotEditUpDownPressed(int)
{
    m_pView->setFocus();
}

void SearchListView::slotViewEnterPressed(const QModelIndex &index)
{
	processItemSelected(index);
}

/**
 * Sets the keyboad focus to the search box.
 */
void SearchListView::slotSetFocus()
{
	m_pEdit->setFocus();
}

/*
 * @index: index in proxyModel
 */
void SearchListView::setCurrentRow(QModelIndex &index)
{
    m_pView->setCurrentIndex(index);
    m_pView->setFocus();
}
