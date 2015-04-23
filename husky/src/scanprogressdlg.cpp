#include <QTextStream>
#include <qlabel.h>
#include <qpushbutton.h>
#include <klocale.h>
#include "scanprogressdlg.h"

/**
 * Class constructor.
 * @param	pParent	The parent widget
 * @param	szName	The widget's name
 */
ScanProgressDlg::ScanProgressDlg(QWidget* pParent) :
    QDialog(pParent),
	m_nFiles(0),
	m_nCurFiles(0)
{
    setupUi(this);
	show();

	// Emit the cancelled() signal when the "Cancel" button is clicked
	connect(m_pCancelButton, SIGNAL(clicked()), this, SIGNAL(cancelled()));
}

/**
 * Class destructor.
 */
ScanProgressDlg::~ScanProgressDlg()
{
}

/**
 * Adds the given number of files to the total count of files already scanned.
 * A visual indication of the progress is given in intervals of more than 100
 * files (to prevent too-frequent GUI updates.)
 * @param	nFiles	The number of files scanned since the last call
 */
void ScanProgressDlg::addFiles(int nFiles)
{
	QString sText;

	// Do nothing if no files were scanned
	if (nFiles <= 0)
		return;

	// Update the total number of files scanned
	m_nFiles += nFiles;
	
	// Update progress only if more than 100 files were scanned since the last
	// update
	if ((m_nFiles - m_nCurFiles) > 100) {
		QTextStream(&sText) << i18n("Scanned ") << m_nFiles << i18n(" files...");
		m_pText->setText(sText);
		m_nCurFiles = m_nFiles;
	}
}

#include "scanprogressdlg.moc"
