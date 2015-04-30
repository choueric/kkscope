#include "stringlistmodel.h"

StringListModel::StringListModel(int columns, QObject *parent):
    QStandardItemModel(0, columns, parent)
{
}

void StringListModel::addItem(const QStringList &item, int row)
{
    if (item.size() != columnCount())
        return;
    insertRow(row);
    for (int i = 0; i < item.size(); i++)
        setData(index(0, i), item.at(i));
}
        
void StringListModel::setIcon(int row, int col, QIcon &icon)
{
    setData(index(row, col), icon, Qt::DecorationRole);
}

void StringListModel::setHeader(const QStringList &item)
{
    if (item.size() != columnCount())
        return;
    for (int i = 0; i < item.size(); i++)
        setHeaderData(i, Qt::Horizontal, item.at(i));
}

QString StringListModel::getString(int row, int col)
{
    return data(index(row, col)).toString();
}
