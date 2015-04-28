#include "searchlistview.h"

        
SearchListView::SearchListView(int searchCol, QWidget *parent) :
    QWidget(parent),
    m_searchCol(searchCol)
{
    m_proxyModel = new QSortFilterProxyModel;
    m_proxyModel->setFilterKeyColumn(m_searchCol);

    m_pView = new QTreeView(this);
    m_pView->setRootIsDecorated(false);
    m_pView->setSortingEnabled(true);
    m_pView->setModel(m_proxyModel);

    m_pEdit = new QLineEdit(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_pEdit);
    layout->addWidget(m_pView);
    setLayout(layout);

    connect(m_pEdit, SIGNAL(textChanged(QString)),
            this, SLOT(slotFindItem()));

	connect(m_pView, SIGNAL(doubleClicked(const QModelIndex &)), 
            this, SLOT(slotItemSelected(const QModelIndex &)));

#if 0
	connect(m_pView, SIGNAL(keyPressed(QKeyEvent*)),
            this, SLOT(slotViewKeyPressed(QKeyEvent*)));
#endif

	connect(m_pEdit, SIGNAL(returnPressed()), 
            this, SLOT(slotItemSelected()));

	connect(m_pEdit, SIGNAL(keyPressed(QKeyEvent*)), 
            this, SLOT(slotEditKeyPressed(QKeyEvent*)));
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
void SearchListView::slotEditKeyPressed(QKeyEvent* pKey)
{
    qDebug() << "TODO:" << __FUNCTION__;
    QApplication::sendEvent(m_pView, pKey);
}

void SearchListView::slotViewKeyPressed(QKeyEvent* pKey)
{
    qDebug() << "TODO:" << __FUNCTION__;
    QApplication::sendEvent(m_pView, pKey);
}

/**
 * Sets the keyboad focus to the search box.
 */
void SearchListView::slotSetFocus()
{
	m_pEdit->setFocus();
}
