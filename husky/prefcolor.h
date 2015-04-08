#ifndef PREFCOLORDLG_H
#define PREFCOLORDLG_H

#include "ui_prefcolorlayout.h"

/**
 * A widget for selecting colours for KScope's main child-windows.
 * @author Elad Lahav
 */
class PrefColor : public QWidget, public Ui_PrefColorLayout
{
   Q_OBJECT

public: 
	PrefColor(QWidget* pParent = 0);
	~PrefColor();

	void load();
	void apply();
	
signals:
	/**
	 * Emitted whenever the user makes a change to the dialogue's input 
	 * widgets.
	 */
	void modified();

protected slots:
	void slotItemSelected(QTreeWidgetItem*);
};

#endif
