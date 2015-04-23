#ifndef PREFFONT_H
#define PREFFONT_H

#include "ui_preffontlayout.h"

/**
 * A widget for selecting fonts for KScope's main child-windows.
 * @author Elad Lahav
 */

class PrefFont : public QWidget, public Ui_PrefFontLayout
{
  Q_OBJECT

public:
	PrefFont(QWidget* pParent = 0);
	~PrefFont();

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
