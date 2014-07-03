#include "mainwin.h"

Mainwin::Mainwin()
{
    openAction = new QAction(tr("&Open"), this);
    saveAction = new QAction(tr("&Save"), this);
    exitAction = new QAction(tr("E&xit"), this);

    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(exit()));

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    textEdit = new QTextEdit;
    p = new SearchTest(0, NULL, "test");

    setCentralWidget(p);

    setWindowTitle(tr("Mainwin"));
}

void Mainwin::open()
{
}

void Mainwin::save()
{
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


