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

    m_pCtagsList = new CtagsListWidget(this);

    connect(&m_ctags, SIGNAL(dataReady(FrontendToken *)), m_pCtagsList,
            SLOT(slotDataReady(FrontendToken *)));
    connect(&m_ctags, SIGNAL(finished(uint)), m_pCtagsList,
            SLOT(slotCtagsFinished(uint)));

    m_pCtagsList->clear();

    const QString path("/home/zhs/workspace/kkscope/husky/test/ctagslist/mainwin.cpp");
    const QStringList list;
    m_ctags.run(path, list);

    setCentralWidget(m_pCtagsList);
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
    printf("open()\n");
}

void Mainwin::save()
{
}
