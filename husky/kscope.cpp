#include "kscope.h"
#include "husky.h"

#include <QStatusBar>

KScope::KScope(QWidget* pParent, const char* szName)
    : KXmlGuiWindow(pParent)
{
    int nTime = 10; 

    dp("KScope Constructor\n");

    //setupGUI(ToolBar | Keys | StatusBar | Save);

	// Show a toolbar show/hide menu
	setStandardToolBarMenuEnabled(true);

	// Create the initial GUI (no active part)
    /*
	setXMLFile("kscopeui.rc");
	createShellGUI();
    */
    setupGUI(Default, "kscopeui.rc");


	// Rebuild the project database after a certain time period has elapsed
	// since the last save
	connect(&m_timerRebuild, SIGNAL(timeout()), this, SLOT(slotRebuildDB()));

	// Reset the rebuild timer
	m_timerRebuild.start(nTime * 1000);
}


/**
 * Class destructor.
 */
KScope::~KScope()
{
    dp("Kscope Destructor\n");
}


/**
 * Handles the "Cscope->Rebuild Database..." command.
 * Rebuilds Cscope's database for the current project.
 */
void KScope::slotRebuildDB()
{
    dp("Rebuild timeout\n");
}

void KScope::initMainWindow()
{
}

/**
 * Opens a project
 * If another project is currently active, it is closed first.
 * @param   sDir    The directory of the project to open.
 */
void KScope::openProject(const QString &sDir)
{
#if 0
    QString sPorjDir;
    ProjectBase *pProj;
    QStringList slQueryFiles;
    QStringList slCallTreeFiles;
    QStringList slArgs;
    ProjectBase::Options opt;
#endif
}
