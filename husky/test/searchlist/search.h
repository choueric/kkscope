#ifndef _SEARCH_H
#define _SEARCH_H

#include <QWidget>
#include <../../searchlist.h>

class SearchTest: public SearchList
{
   Q_OBJECT
    
public:
	SearchTest(int nSearchCol, QWidget* pParent = 0, const char* szName = 0);
	~SearchTest();
	bool getTip(QListWidgetItem* pItem, QString& sTip);

	void processItemSelected(QListWidgetItem* pItem);
};
    

#endif
