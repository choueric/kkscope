#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>
#include <iostream>

#include "../../searchlist.h"
#include "mainwin.h"

int main(int argc, char **argv)
{
    KAboutData aboutData( "husky_test", "husky_test",
        ki18n("husky_test"), "0.1",
        ki18n("test."),
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

    Mainwin *p = new Mainwin;
    p->show();

    return app.exec();
}
