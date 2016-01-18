#ifndef BOOKMARKSDLG_H
#define BOOKMARKSDLG_H

#include "ui_bookmarkslayout.h"

class BookmarksDlg : public QDialog, public Ui_BookmarksLayout
{
Q_OBJECT

public:
	BookmarksDlg(QWidget* pParent = 0);
	~BookmarksDlg();

	QueryView* getView() { return m_pView; }
	void getBookmark(QString&, uint&);
	
private:
	QString m_sPath;
	uint m_nLine;
	
private slots:
	void slotLineRequested(const QString&, uint);	
};

#endif

