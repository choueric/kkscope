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

    setWindowTitle(tr("Mainwin"));

    pFileList = new FileList(this, "test file list");
    setCentralWidget(pFileList);
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
    static int i = 0;
    if (i == 0)
        pFileList->addItem("/home/zhs/test1.cpp");
    else if (i == 1)
        pFileList->addItem("/home/zhs/test2.cpp");
    else if (i == 2)
        pFileList->addItem("/home/zhs/make.cpp");
    else if (i == 3)
        pFileList->addItem("/home/zhs/make.h");
    else
        pFileList->addItem("/home/zhs/default.cpp");
    i++;
}

void Mainwin::save()
{
}
