#ifndef _SEARCHLISTVIEW_H_
#define _SEARCHLISTVIEW_H_

#include <QtGui>

class ListTreeView : public QTreeView
{
    Q_OBJECT

    public:
        ListTreeView(QWidget *parent = 0);
        ~ListTreeView();

    signals:
        void enterPressed(const QModelIndex &);

    protected:
        void mouseDoubleClickEvent(QMouseEvent*);
        void keyPressEvent(QKeyEvent *pEvent);
};

class ListLineEdit : public QLineEdit
{
    Q_OBJECT

    public:
        ListLineEdit(QWidget *parent = 0);
        ~ListLineEdit();

    signals:
        void upDownPressed(int);

    protected:
        void keyPressEvent(QKeyEvent *pEvent);
};

class SearchListView: public QWidget
{
    Q_OBJECT

    public:
        SearchListView(int searchCol, QWidget *parent = 0);
        ~SearchListView();

        void setSourceModel(QAbstractItemModel *model);
        virtual bool getTip(QModelIndex &index, QString& sTip) = 0;

    public slots:
        void slotSetFocus();

    private slots:
        void slotFindItem();
        void slotItemSelected(const QModelIndex &);
        void slotItemSelected();
        void slotEditUpDownPressed(int);
        void slotViewEnterPressed(const QModelIndex &index);

    protected:
        ListTreeView *m_pView;
        ListLineEdit *m_pEdit;
        QSortFilterProxyModel *m_proxyModel;
        int m_searchCol;

        /**
         * Called whenever the user selects an item in the list by either double-
         * clicking it, or by highlighting the item and pressing the ENTER key.
         * @param	pItem	The selected list item
         */
        virtual void processItemSelected(const QModelIndex &) = 0;
        //void MousePressEvent(QMouseEvent *pEvent);
        //void keyPressEvent(QKeyEvent *pEvent);
};

#endif
