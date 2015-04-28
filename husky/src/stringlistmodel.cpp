#include "stringlistmodel.h"

StringListModel::StringListModel(int columns, QObject *parent):
    QStandardItemModel(0, columns, parent)
{
}

void StringListModel::addItem(const QStringList &item)
{
    if (item.size() != columnCount())
        return;
    insertRow(0);
    for (int i = 0; i < item.size(); i++)
        setData(index(0, i), item.at(i));
}

        
void StringListModel::setHeader(const QStringList &item)
{
    if (item.size() != columnCount())
        return;
    for (int i = 0; i < item.size(); i++)
        setHeaderData(i, Qt::Horizontal, item.at(i));
}
