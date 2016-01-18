#ifndef PREFOPT_H
#define PREFOPT_H

#include "ui_prefoptlayout.h"

/**
 * A widget for setting different global options.
 * @author Elad Lahav
 */
 
class PrefOpt : public QWidget, public Ui_PrefOptLayout
{
	Q_OBJECT

public:
	PrefOpt(QWidget* pParent = 0);
	~PrefOpt();

	void load();
	void apply();
	
signals:
	/**
	 * Emitted whenever the user makes a change to the dialogue's input 
	 * widgets.
	 */
	void modified();
};

#endif

