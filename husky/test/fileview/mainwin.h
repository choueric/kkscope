#ifndef _NOTEPAD_H
#define _NOTEPAD_H

#include <QtGui>
#include <KParts/MainWindow>
#include <QtGui/QKeyEvent>

#include <KTextEditor/Document>
#include <KTextEditor/View>
#include <KTextEditor/Editor>
#include <KTextEditor/EditorChooser>

#include "../../fileview.h"

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
        QAction *openAction;
        QAction *saveAction;
        QAction *exitAction;

        FileView *p_test;
};

#endif

