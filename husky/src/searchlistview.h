#ifndef _SEARCHLISTVIEW_H_
#define _SEARCHLISTVIEW_H_

#include <QtGui>

class SearchListView: public QWidget
{
    Q_OBJECT

    public:
        SearchListView(int searchCol, QWidget *parent = 0);
        ~SearchListView();

        void setSourceModel(QAbstractItemModel *model);
        void slotItemSelected(const QModelIndex &index);
        void slotItemSelected();
        void slotEditKeyPressed(QKeyEvent*);
        void slotViewKeyPressed(QKeyEvent*);
	
        virtual bool getTip(QModelIndex &index, QString& sTip) = 0;

    public slots:
        void slotSetFocus();

    private slots:
        void slotFindItem();

    protected:
        QTreeView *m_pView;
        QLineEdit *m_pEdit;
        QSortFilterProxyModel *m_proxyModel;
        int m_searchCol;

        /**
         * Called whenever the user selects an item in the list by either double-
         * clicking it, or by highlighting the item and pressing the ENTER key.
         * @param	pItem	The selected list item
         */
        virtual void processItemSelected(const QModelIndex &) = 0;
};

#endif
