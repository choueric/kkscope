#ifndef CSCOPEMSGDLG_H
#define CSCOPEMSGDLG_H

#include "ui_cscopemsglayout.h"

/**
 * Displays messages sent by Cscope to its standard error stream.
 * @author	Elad Lahav
 */
class CscopeMsgDlg : public QDialog, public Ui_CscopeMsgLayout
{
	Q_OBJECT

public:
	CscopeMsgDlg(QWidget* pParent = 0);
	~CscopeMsgDlg();
	
	void addText(const QString&);
};

#endif

