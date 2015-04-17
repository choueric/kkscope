#include "bookmarksdlg.h"
#include "queryview.h"

BookmarksDlg::BookmarksDlg(QWidget* pParent):
    QDialog(pParent)
{
    setupUi(this);
	// Do not show the "Function" column
	m_pView->setColumnWidth(0, 0);
	
	// Handle requests for source locations
	connect(m_pView, SIGNAL(lineRequested(const QString&, uint)), this,
		SLOT(slotLineRequested(const QString&, uint)));
}

BookmarksDlg::~BookmarksDlg()
{
}

void BookmarksDlg::getBookmark(QString& sPath, uint& nLine)
{
	sPath = m_sPath;
	nLine = m_nLine;
}

void BookmarksDlg::slotLineRequested(const QString& sPath, uint nLine)
{
	m_sPath = sPath;
	m_nLine = nLine;
	accept();
}

#include "bookmarksdlg.moc"

