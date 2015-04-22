#include "mainwin.h"

#include <KApplication>
#include <KAction>
#include <KLocale>
#include <KActionCollection>
#include <KStandardAction>
#include <KFileDialog>
#include <KMessageBox>
#include <KIO/NetAccess>
#include <KSaveFile>
#include <QTextStream>
#include <KXMLGUIFactory>

#include <KTextEditor/Document>
#include <KTextEditor/View>
#include <KTextEditor/Editor>
#include <KTextEditor/EditorChooser>

Mainwin::Mainwin()
{
    openAction = new QAction(tr("&Open"), this);
    saveAction = new QAction(tr("&Save"), this);
    exitAction = new QAction(tr("E&xit"), this);

    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(exit()));

    setWindowTitle(tr("Mainwin"));

    p_test = new QueryView(this);
    p_test->addRecord("first", NULL, NULL, NULL, NULL);
    p_test->addRecord("second", NULL, NULL, NULL, NULL);
    p_test->addRecord("third", NULL, NULL, NULL, NULL);
    p_test->show();
    setCentralWidget(p_test);
}

void Mainwin::exit()
{
    QMessageBox msgBox;

    msgBox.setWindowTitle(tr("Mainwin"));
    msgBox.setText(tr("Do you really want to quit?"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    if (msgBox.exec() == QMessageBox::Yes)
        qApp->quit();
}

void Mainwin::open()
{
}

void Mainwin::save()
{
}
