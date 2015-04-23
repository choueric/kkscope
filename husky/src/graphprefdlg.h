#ifndef GRAPHPREFDLG_H
#define GRAPHPREFDLG_H

#include "ui_graphpreflayout.h"

/**
 * A dialogue that allows the user to configure the appearance and behaviour
 * of the call graph.
 * @author Elad Lahav
 */
class GraphPrefDlg : public QDialog, public Ui_GraphPrefLayout
{
	Q_OBJECT

public:
	GraphPrefDlg(QWidget* pParent = 0);
	~GraphPrefDlg();

	int getMaxNodeDegree();

protected slots:
	virtual void slotFontClicked();
	virtual void slotColorClicked();
};

#endif

