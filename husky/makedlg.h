#ifndef MAKEDLG_H
#define MAKEDLG_H

#include <QDialog>
#include "ui_makelayout.h"

class MakeFrontend;
class FrontendToken;

/**
 * A window that displays the output of make-like commands.
 * The window contains a text browser showing errors as links to source
 * locations.
 * The make process is determined by a user-specified command, and is run in
 * a user-specified directory. Controls are provided for modifying these values.
 * @author Elad Lahav
 */
class MakeDlg: public QDialog, public Ui_MakeLayout
{
	Q_OBJECT
	
public:
	MakeDlg(QWidget* pParent = 0);
	virtual ~MakeDlg();
	
	QString getCommand() const;
	void setCommand(const QString&);
	QString getDir() const;
	void setDir(const QString&);
	
public slots:
	virtual void slotMake();
	
signals:
	void fileRequested(const QString&, uint);
	
protected:
	virtual void closeEvent(QCloseEvent*);
	
protected slots:
	virtual void slotStop();
	void slotShowOutput(FrontendToken*);
	void slotFinished(uint);
	void slotBrowserClicked(const QString&);
	void slotAddError(const QString&, const QString&, const QString&);
	
private:
	/** Handles the make process. */
	MakeFrontend* m_pMake;
};

#endif
