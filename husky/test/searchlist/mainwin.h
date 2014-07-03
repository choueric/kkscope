#ifndef _NOTEPAD_H
#define _NOTEPAD_H

#include <QtGui>
#include "search.h"

class Mainwin: public QMainWindow
{
    Q_OBJECT

    public:
        Mainwin();

    private slots:
        void open();
        void save();
        void exit();

    private:
        QTextEdit *textEdit;
        SearchTest *p;

        QAction *openAction;
        QAction *saveAction;
        QAction *exitAction;

        QMenu *fileMenu;
};

#endif

