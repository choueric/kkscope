#include "search.h"

SearchTest::SearchTest(int nSearchCol, QWidget* pParent, const char* szName) :
    SearchList(nSearchCol, pParent, szName)
{
}


SearchTest::~SearchTest()
{
}

bool SearchTest::getTip(QListWidgetItem* pItem, QString& sTip)
{
    return true;
}


void SearchTest::processItemSelected(QListWidgetItem* pItem)
{
}

//#include "search.moc"
