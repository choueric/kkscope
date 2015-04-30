#ifndef _STRINGLISTMODEL_H_
#define _STRINGLISTMODEL_H_

#include <QtGui>

class StringListModel : public QStandardItemModel
{
    Q_OBJECT

    public:
        StringListModel(int columns, QObject *parent = 0);
        void setHeader(const QStringList &item);
        void addItem(const QStringList &item, int row = 0);
        void setIcon(int row, int col, QIcon &icon);
        QString getString(int row, int col);

    private:
};

#endif
