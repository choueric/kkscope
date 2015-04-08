#include <qcheckbox.h>
#include <qtextedit.h>
#include <kurlrequester.h>
#include <klineedit.h>
#include <kstandarddirs.h>
#include <klocale.h>
#include "preffrontend.h"
#include "kscopeconfig.h"
#include "configfrontend.h"

/**
 * Class constructor.
 * @param	pParent	The parent widget
 * @param	szName	The widget's name
 */
PrefFrontend::PrefFrontend(QWidget* pParent)
{
    setupUi(this);
	// Set initial values
	load();

	// Attempt to guess paths based on the user's PATH environment variable
	connect(m_pGuessButton, SIGNAL(clicked()), this,
		SLOT(slotGuessPaths()));	
		
	// Emit the modified() signal when a new path is set
	connect(m_pCscopeURL, SIGNAL(textChanged(const QString&)), this,
		SIGNAL(modified()));
	connect(m_pCtagsURL, SIGNAL(textChanged(const QString&)), this,
		SIGNAL(modified()));
	connect(m_pDotURL, SIGNAL(textChanged(const QString&)), this,
		SIGNAL(modified()));
}

/**
 * Class destructor.
 */
PrefFrontend::~PrefFrontend()
{
}

/**
 * Reads the current settings from the configuration object, and applies them
 * the the page's widget.
 */
void PrefFrontend::load()
{
	m_pCscopeURL->lineEdit()->setText(Config().getCscopePath());
	m_pCtagsURL->lineEdit()->setText(Config().getCtagsPath());
	m_pDotURL->lineEdit()->setText(Config().getDotPath());
}

/**
 * Commits settings changes to the configuration object.
 */
void PrefFrontend::apply()
{
	Config().setCscopePath(m_pCscopeURL->text());
	Config().setCtagsPath(m_pCtagsURL->text());
	Config().setDotPath(m_pDotURL->text());
}

/**
 * Emits the modified() signal whenever any of the paths edit widgets changes
 * its contents.
 * This slot is connected to the textChanged() signal of each of the path
 * edit widgets. By emitting the modified() signal, the widget notifies the
 * parent dialog it should enable the "Apply" button.
 */
void PrefFrontend::slotChanged(const QString&)
{
	emit modified();
}

/**
 * Checks the user's PATH environment variable for a Cscope and Ctags
 * executables.
 * This is done by running the kscope_config script.
 */
void PrefFrontend::slotGuessPaths()
{
	ConfigFrontend* pConf;
	
	// Start with an empty results text widget
	m_pScriptText->clear();
	
	// Create a frontend object for the script
	pConf = new ConfigFrontend(true);
	
	// Show tests and results in the text widget
	connect(pConf, SIGNAL(test(uint)), this,
		SLOT(slotAutoConfigTest(uint)));
	connect(pConf, SIGNAL(result(uint, const QString&)), this,
		SLOT(slotAutoConfigResult(uint, const QString&)));
	
	// Run the script
	pConf->run(m_pCscopeURL->text(), m_pCtagsURL->text(),
		m_pDotURL->text());
}

/**
 * Shows the test being executed by the script in the text widget.
 * This slot is connected to the test() signal of the ConfigFrontend object.
 * @param	nType	The type of test being executed
 */
void PrefFrontend::slotAutoConfigTest(uint nType)
{
	switch (nType) {
	case ConfigFrontend::CscopePath:
		m_pScriptText->append(i18n("Looking for Cscope..."));
		break;
		
	case ConfigFrontend::CscopeVersion:
		m_pScriptText->append(i18n("Checking Cscope version..."));
		break;
		
	case ConfigFrontend::CscopeVerbose:
		m_pScriptText->append(i18n("Cscope support for line mode verbose "
			"output..."));
		break;
		
	case ConfigFrontend::CscopeSlowPath:
		m_pScriptText->append(i18n("Cscope support slow path definitions... "));
		break;
			
	case ConfigFrontend::CtagsPath:
		m_pScriptText->append(i18n("Looking for Ctags..."));
		break;
					
	case ConfigFrontend::CtagsExub:
		m_pScriptText->append(i18n("Ctags compatibilty with ctags-exuberant"
			"..."));
		break;
			
	case ConfigFrontend::DotPath:
		m_pScriptText->append(i18n("Looking for Dot..."));
		break;
					
	case ConfigFrontend::DotPlain:
		m_pScriptText->append(i18n("Checking -Tplain..."));
		break;
	}
}

/**
 * Shows the result of a test executed by the configuration script, and
 * adjusts the configuration widgets accordingly.
 * @param	nType	The type of test that was executed
 * @param	sResult	The test's result
 */
void PrefFrontend::slotAutoConfigResult(uint nType, const QString& sResult)
{
	QString sLine;
	
	sLine = sResult + "\n";
		
	switch (nType) {
	case ConfigFrontend::CscopePath:
		m_pScriptText->append(sLine);
		if (sResult == "ERROR")
			m_pCscopeURL->lineEdit()->setText("");
		else
			m_pCscopeURL->lineEdit()->setText(sResult);
			
		break;
	
	case ConfigFrontend::CscopeVersion:
		m_pScriptText->append(sLine);
		if (sResult == "ERROR")
			m_pCscopeURL->lineEdit()->setText("");
		break;
	
	case ConfigFrontend::CscopeVerbose:
		m_pScriptText->append(sLine);
		break;
	
	case ConfigFrontend::CscopeSlowPath:
		m_pScriptText->append(sLine);
		break;
		
	case ConfigFrontend::CtagsPath:
		m_pScriptText->append(sLine);
		if (sResult == "ERROR")
			m_pCtagsURL->lineEdit()->setText("");
		else
			m_pCtagsURL->lineEdit()->setText(sResult);
		break;
	
	case ConfigFrontend::CtagsExub:
		m_pScriptText->append(sLine);
		if (sResult == "ERROR")
			m_pCtagsURL->lineEdit()->setText("");
		break;
	
	case ConfigFrontend::DotPath:
		m_pScriptText->append(sLine);
		if (sResult == "ERROR")
			m_pDotURL->lineEdit()->setText("");
		else
			m_pDotURL->lineEdit()->setText(sResult);
		break;
	
	case ConfigFrontend::DotPlain:
		m_pScriptText->append(sLine);
		if (sResult == "ERROR")
			m_pDotURL->lineEdit()->setText("");
		break;
	}
}

#include "preffrontend.moc"
