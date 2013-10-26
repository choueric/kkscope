#ifndef KSCOPE_H
#define KSCOPE_H

#include <QtGui>
#include <QTimer>
#include <kparts/mainwindow.h>
#include <KXmlGuiWindow>

class KScope : public KXmlGuiWindow
{
	Q_OBJECT

public:
	KScope(QWidget *pParent = 0, const char *szName = 0);
	~KScope();

    void openProject(const QString &);

private:
    QTimer m_timerRebuild;

    void initMainWindow();

private slots:
	void slotRebuildDB();

};

#endif
