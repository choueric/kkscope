#include <qtextedit.h>
#include <qpushbutton.h>
#include "cscopemsgdlg.h"

/**
 * Class constructor.
 * @param	pParent	The parent widget
 * @param	szName	The widget's name
 */
CscopeMsgDlg::CscopeMsgDlg(QWidget* pParent)
{
    setupUi(this);
	// Hide the dialog when the "Hide" button is clicked
	connect(m_pHideButton, SIGNAL(clicked()), this, SLOT(hide()));
	
	// Clear all messages when the "Clear" button is clicked
	connect(m_pClearButton, SIGNAL(clicked()), m_pMsgText, SLOT(clear()));
}

/**
 * Class destructor.
 */
CscopeMsgDlg::~CscopeMsgDlg()
{
}

/**
 * Appends a given message to the text box.
 * After a new messsage is added, the dialog becomes visible.
 * @param	sText	The text of the message to add
 */
void CscopeMsgDlg::addText(const QString& sText)
{
	m_pMsgText->append(sText);
	show();
}

#include "cscopemsgdlg.moc"

