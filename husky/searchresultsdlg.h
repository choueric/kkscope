#ifndef SEARCHRESULTSDLG_H
#define SEARCHRESULTSDLG_H

#include <qregexp.h>
#include <qcheckbox.h>
#include "ui_searchresultslayout.h"

/**
 * A dialogue for defining searches on query results.
 * The dialogue is activated from the query results menu.
 * @author Elad Lahav
 */
class SearchResultsDlg : public QDialog, public Ui_SearchResultsLayout
{
	Q_OBJECT

public:
	SearchResultsDlg(QWidget* pParent = 0, const char* szName = 0);
	~SearchResultsDlg();

	void setColumn(int);
	int getColumn();
	void getPattern(QRegExp&);
		
	/**
	 * @return	true if the search pattern should be negated, false otherwise
	 */
	bool isNegated() { return m_pNegateCheck->isChecked(); }
	
protected slots:
	virtual void accept();
	
private:
	/** Possible search types. */
	enum { PlainText = 0, RegExp, SimpRegExp };
	
	/** Remembers the last search type. */
	static int s_nType;
	
	/** Remembers the last value of the Case Sensitive check-box. */
	static Qt::CaseSensitivity s_bCaseSensitive;
	
	/** Remembers the last value of the Negate Search check-box. */
	static bool s_bNegate;
};

#endif
