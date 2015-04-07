#ifndef OPENPROJECTDLG_H
#define OPENPROJECTDLG_H

#include <qwidget.h>
#include "ui_openprojectlayout.h"

/**
 * A dialogue for selecting a project to open.
 * Allows projects to be searched, and displays a list of previosuly loaded
 * projects.
 * @author Elad Lahav
 */

class OpenProjectDlg : public QDialog, public Ui_OpenProjectLayout
{
	Q_OBJECT

public: 
	OpenProjectDlg(QWidget* pParent = 0);
	~OpenProjectDlg();

	QString getPath() const;

protected slots:
	virtual void slotProjectSelected(const QString&);
	virtual void slotRemoveRecent();
	virtual void slotSelectRecent(QListWidgetItem*);
	virtual void slotOpenRecent(QListWidgetItem*);

private:
	void loadRecent();
};

#endif
