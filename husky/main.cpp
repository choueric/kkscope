#include <KApplication>
#include <kcmdlineargs.h>
#include <kaboutdata.h>
#include <KLocale>

#include "kscope.h"
#include "kscopeconfig.h"

#define VERSION "2.0"


/**
 * Defines the programme's entry point.
 * Creates KScope's main window, and starts the event loop.
 * @param	argc	Number of command line arguments
 * @param	argv	Command line arguments
 * @return	Programme's exit value
 */
int main(int argc, char *argv[])
{
    QByteArray version(VERSION);
	// Create the "About" dialogue
	KAboutData aboutData("kscope", 0, ki18n("KScope"), version,
            ki18n("KScope\nA source-editing environment for KDE, based on Cscope"),
            KAboutData::License_BSD, ki18n("(c) 2003-2007, Elad Lahav"), KLocalizedString(), "http://kscope.sourceforge.net",
		"zhssmail@gmail.com");
	aboutData.addAuthor(ki18n("Elad Lahav"), ki18n("Developer"), "elad_lahav@users.sf.net");
	aboutData.addAuthor(ki18n("eric chou"), ki18n("Developer"), "zhssmail@gmail.com", "ericnode.info");
	aboutData.addCredit(ki18n("Albert Yosher"), ki18n("Code completion, patches and bug fixes"), "ayosher@users.sf.net");
	aboutData.addCredit(ki18n("Gabor Fekete"), ki18n("Bug fixes and patches"), "feketgai@index.hu");

    KCmdLineOptions options;
    options.add("+[CSCOPE.OUT path]", ki18n("Opens a cscope.out file in a temporary project"), 0);
    options.add("+[CSCOPE.PROJ path | KScope project directory path]", ki18n("Opens a KScope project"), 0);
	
	// Initialise command-line argument parsing
	KCmdLineArgs::init(argc, argv, &aboutData);
	KCmdLineArgs::addCmdLineOptions(options);

	// Parse command line arguments
	KCmdLineArgs* pArgs = KCmdLineArgs::parsedArgs();

	// Create the main window
	KApplication app;
	KScope* pKScope = new KScope();

	// app.setTopWidget(pKScope); // no need if use KMainWindow
	
	// Display the main window
	pKScope->show();  

	// Handle command-line arguments
	if (pArgs->count() > 0) {
		pKScope->parseCmdLine(pArgs);
	} else if (Config().getLoadLastProj()) {
		// No arguments given, load the most recent project
		pKScope->openLastProject();
	}
	
	// Make sure Cscope is properly installed
	pKScope->verifyCscope();
	
	// Start the event loop
	return app.exec();
}
