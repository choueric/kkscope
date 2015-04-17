#include <qpushbutton.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qradiobutton.h>
#include "searchresultsdlg.h"

int SearchResultsDlg::s_nType = PlainText;
Qt::CaseSensitivity SearchResultsDlg::s_bCaseSensitive = Qt::CaseSensitive;
bool SearchResultsDlg::s_bNegate = false;

/**
 * Class constructor.
 * @param	pParent	The parent widget
 * @param	szName	Optional widget name
 */
SearchResultsDlg::SearchResultsDlg(QWidget* pParent) :
    QDialog(pParent)
{
    setupUi(this);
	// Select the last selected type radio button
	switch (s_nType) {
	case PlainText:
		m_pTextRadio->setChecked(true);
		break;
		
	case RegExp:
		m_pRegExpRadio->setChecked(true);
		break;
		
	case SimpRegExp:
		m_pSimpRegExpRadio->setChecked(true);
		break;
	}

	// Set the default value of the check-boxes
	m_pCaseSenCheck->setChecked(s_bCaseSensitive);
	m_pNegateCheck->setChecked(s_bNegate);
		
	// Terminate the dialogue when either the "OK" or "Cancel" buttons are
	// clicked
	connect(m_pOKButton, SIGNAL(clicked()), this, SLOT(accept()));
	connect(m_pCancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

/**
 * Class destructor.
 */
SearchResultsDlg::~SearchResultsDlg()
{
}

/**
 * Determines the default column on which to search.
 * The column's name appears in the column combo-box.
 */
void SearchResultsDlg::setColumn(int nCol)
{
	m_pColumnCB->setCurrentIndex(nCol);
}

/**
 * @return	The selected column on which to perform the search
 */
int SearchResultsDlg::getColumn()
{
	return m_pColumnCB->currentIndex();
}

/**
 * Creates a regular expression based on the given pattern and type of search.
 * @param	re	A regular expression object to set
 */
// TODO: pattern syntax may be wrong
void SearchResultsDlg::getPattern(QRegExp& re)
{
	QString sPattern;
	
	sPattern = m_pSearchEdit->text();
	
	// Create the regular expression
	switch (s_nType) {
	case PlainText:
		re.setPattern(QRegExp::escape(sPattern));
		re.setPatternSyntax(QRegExp::FixedString);
		break;
		
	case RegExp:
		re.setPattern(sPattern);
		re.setPatternSyntax(QRegExp::RegExp);
		break;
	
	case SimpRegExp:
		re.setPattern(sPattern);
		re.setPatternSyntax(QRegExp::RegExp2);
		break;
	}
	
	// Set the case-(in)sensitive parameter
	re.setCaseSensitivity(s_bCaseSensitive);
}

/**
 * Reads user values from the widgets, and closes the dialogue.
 * This slot is connected to the clicked() signal emitted by the "OK" button.
 */
void SearchResultsDlg::accept()
{
	QString sText;
		
	// Determine the selected type and store its value for the next invocation
	if (m_pTextRadio->isChecked())
		s_nType = PlainText;
	else if (m_pRegExpRadio->isChecked())
		s_nType = RegExp;
	else if (m_pSimpRegExpRadio->isChecked())
		s_nType = SimpRegExp;
	
	// Determine search parameters
	s_bCaseSensitive = m_pCaseSenCheck->isChecked() ? Qt::CaseSensitive: Qt::CaseInsensitive;
	s_bNegate = m_pNegateCheck->isChecked();
	
	// Remove white space from the search text
	sText = m_pSearchEdit->text();
	sText.trimmed();
	if (sText.isEmpty()) {
		QDialog::reject();
		return;
	}

	// Close the dialogue
	QDialog::accept();
}

#include "searchresultsdlg.moc"

