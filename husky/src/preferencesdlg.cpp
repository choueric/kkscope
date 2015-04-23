#include <qlayout.h>
#include <klocale.h>
#include <kiconloader.h>
#include <kurlrequester.h>
#include <klineedit.h>
#include <qcheckbox.h>
#include <kcolorbutton.h>
#include <kmessagebox.h>
#include <kfontrequester.h>
#include <KPageDialog>
#include <KPageWidgetItem>

#include "preferencesdlg.h"
#include "preffrontend.h"
#include "prefcolor.h"
#include "preffont.h"
#include "prefopt.h"
#include "kscopeconfig.h"
#include "cscopefrontend.h"
#include "ctagsfrontend.h"
#include "dotfrontend.h"


/**
 * Class constructor.
 * @param	nPage	The initial page to show
 * @param	pParent	The parent widget
 * @param	szName	The widget's name
 */
PreferencesDlg::PreferencesDlg(QWidget* pParent, uint nPage) :
	//KDialogBase(IconList, i18n("Preferences"), Default | Ok | Apply | Cancel, Ok, pParent, 0)
    KPageDialog(pParent)
{
	QVBoxLayout* pLayout;
    KPageWidgetItem *pFrame;
    uint index = 0;
    KPageWidgetItem *pCur = NULL;
    
    setCaption(i18n("Preferences"));

    // iconName refer to standards.freedesktop.org/icon-naming-spec
    // or look up in /usr/share/icons/

	// Create and add the "Frontend" page
	pLayout = new QVBoxLayout;
	m_pPrefFrontend = new PrefFrontend(this);
	pLayout->addWidget(m_pPrefFrontend);
	pFrame = addPage(m_pPrefFrontend, i18n("Programmes"));
	pFrame->setHeader(i18n("Paths to back-end programmes"));
    pFrame->setIcon(KIcon("system-run"));
    if (nPage == index++)
        pCur = pFrame;

	
	// Create and add the "Colours" page
	pLayout = new QVBoxLayout;
	m_pPrefColor = new PrefColor(this);
	pLayout->addWidget(m_pPrefColor);
	pFrame = addPage(m_pPrefColor, i18n("Colours"));
    pFrame->setHeader(i18n("Window colours"));
    pFrame->setIcon(KIcon("preferences-desktop-color"));
    if (nPage == index++)
        pCur = pFrame;
	
	// Create and add the "Fonts" page
	pLayout = new QVBoxLayout;
	m_pPrefFont = new PrefFont(this);
	pLayout->addWidget(m_pPrefFont);
	pFrame = addPage(m_pPrefFont, i18n("Fonts"));
    pFrame->setHeader(i18n("Window fonts"));
    pFrame->setIcon(KIcon("preferences-desktop-font"));
    if (nPage == index++)
        pCur = pFrame;
	
	// Create and add the "Options" page
	pLayout = new QVBoxLayout;
	m_pPrefOpt = new PrefOpt(this);
	pLayout->addWidget(m_pPrefOpt);
	pFrame = addPage(m_pPrefOpt, i18n("Options"));
    pFrame->setHeader(i18n("Misc. Options"));
    pFrame->setIcon(KIcon(KIconLoader::global()->loadIcon("package_settings", KIconLoader::Panel, 0, false)));
    pFrame->setIcon(KIcon("configure"));
    if (nPage == index++)
        pCur = pFrame;

	// Make sure the "Apply" button is initially disabled
	enableButtonApply(false);
		
	// Enable the "Apply" button when a parameter changes its value
	connect(m_pPrefFrontend, SIGNAL(modified()), this, 
		SLOT(slotModified()));
	connect(m_pPrefColor, SIGNAL(modified()), this, SLOT(slotModified()));
	connect(m_pPrefFont, SIGNAL(modified()), this, SLOT(slotModified()));
	connect(m_pPrefOpt, SIGNAL(modified()), this, SLOT(slotModified()));
	
	// Set the active page
    if (pCur)
        setCurrentPage(pCur);
    show();
}

/**
 * Class destructor.
 */
PreferencesDlg::~PreferencesDlg()
{
}

/**
 * Updates the dialog's widgets with the current configuration parameters.
 */
void PreferencesDlg::loadConfig()
{
	m_pPrefFrontend->load();
	m_pPrefColor->load();
	m_pPrefFont->load();
	m_pPrefOpt->load();
}

/**
 * Sets the configured parameters to the global configuration object.
 * This method is called when either the "OK" or the "Apply" button are
 * clicked. Before the new settings are applied, their values are verified.
 * @return	true if the new parameters were applied successfully, false
 *			otherwise
 */
bool PreferencesDlg::updateConfig()
{
	// Verify configured paths lead to the executables
	if (!verifyPaths())
		return false;

	// Apply the changes
	m_pPrefFrontend->apply();
	m_pPrefColor->apply();
	m_pPrefFont->apply();
	m_pPrefOpt->apply();
	
	emit applyPref();
	return true;
}

/**
 * Tests whether the paths set for Cscope and Ctags lead to executables.
 * Cscope is verified by a different process.
 */
bool PreferencesDlg::verifyPaths()
{
	return (CtagsFrontend::verify(m_pPrefFrontend->m_pCtagsURL->text()) &&
		DotFrontend::verify(m_pPrefFrontend->m_pDotURL->text()));
    return false;
}

/**
 * Updates the global configuration based on the values given in the 
 * preferences dialogue, and then closes the dialogue.
 * This function is called after the user clicks the dialogue's "OK" button.
 */
void PreferencesDlg::accept()
{
	if (updateConfig())
		KPageDialog::accept();
}

/**
 * Updates the global configuration based on the values given in the 
 * preferences dialogue, leaving the dialogue open.
 * This function is called after the user clicks the dialogue's "Apply" 
 * button.
 */
void PreferencesDlg::slotApply()
{
	if (updateConfig())
		enableButtonApply(false);
}

/**
 * Resets all configuration parameters to their default values.
 * This slot is called when the user clicks the "Default" button.
 */
void PreferencesDlg::slotDefault()
{
	// Prompt the user before applying default values
	if (KMessageBox::questionYesNo(0, i18n("This would reset all your "
		"configuration settings! Continue?")) == KMessageBox::Yes) {
		// Load the default values
		Config().loadDefault();
		loadConfig();

		// Apply the default values
		slotApply();
	}
}

/**
 * Enables the "Apply" button.
 */
void PreferencesDlg::slotModified()
{
	enableButtonApply(true);
}

#include "preferencesdlg.moc"
