#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>


#include "husky.h"
#include "kscope.h"

int main(int argc, char **argv)
{
    KAboutData aboutData( "husky", "husky",
        ki18n("husky"), "0.1",
        ki18n("modification of kscope."),
        KAboutData::License_GPL,
        ki18n("Copyright (c) 2013") );

    KCmdLineArgs::init( argc, argv, &aboutData );

    KCmdLineOptions options;
    options.add("+[file]", ki18n("demo argument"));
    KCmdLineArgs::addCmdLineOptions(options);
 
    // parse command line arguments
    KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
    if(args->count()) {
        std::cout << "have args " << args->count() << std::endl;
    }
 
    KApplication app;

    KScope *pKScope = new KScope();
    pKScope->show();

    return app.exec();
}
