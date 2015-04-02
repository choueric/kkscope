#ifndef SCANPROGRESSDLG_H
#define SCANPROGRESSDLG_H

#include <qwidget.h>
#include "ui_scanprogresslayout.h"

/**
 * Displays the progress of a file scan operation.
 * This dialogue is displayed while a ProjectFilesDlg dialogue scans a
 * directory tree for all files matching the patterns defined for the
 * project's source files.
 * @author Elad Lahav
 */

class ScanProgressDlg : public QDialog, public Ui_ScanProgressLayout
{
   Q_OBJECT

public: 
	ScanProgressDlg(QWidget* pParent = 0);
	~ScanProgressDlg();

	void addFiles(int);

signals:
	/**
	 * Indicates that the dialogue's "Cancel" button hsa been clicked by the
	 * user.
	 */
	void cancelled();
	
private:
	/** The total number of files scanned thus far. */
	int m_nFiles;
	
	/** The number of files currently displayed in the progress report (which
		may be smaller than m_nFiles since not every call to addFiles() updates
		the progress display.)*/
	int m_nCurFiles;
};

#endif
