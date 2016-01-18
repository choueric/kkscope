#ifndef PREFFRONTENDDLG_H
#define PREFFRONTENDDLG_H

#include <qwidget.h>
#include "ui_preffrontendlayout.h"

/**
 * A widget for setting the paths to various programmes to which KScope
 * provides a front-end.
 * @author Elad Lahav
 */

class PrefFrontend : public QWidget, public Ui_PrefFrontendLayout
{
   Q_OBJECT

public: 
	PrefFrontend(QWidget* pParent = 0);
	~PrefFrontend();

	void load();
	void apply();
	
signals:
	/**
	 * Emitted whenever the user makes a change to the dialogue's input 
	 * widgets.
	 */
	void modified();
	
private slots:
	void slotChanged(const QString&);
	void slotGuessPaths();
	void slotAutoConfigTest(uint);
	void slotAutoConfigResult(uint, const QString&);
};

#endif
