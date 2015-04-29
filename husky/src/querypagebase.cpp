#include <QTreeWidgetItemIterator>
#include <qfile.h>
#include "querypagebase.h"
#include "queryview.h"
#include "kscopeconfig.h"

#define FILE_VERSION	"VERSION=2"

/**
 * Class constructor.
 * @param	pParent	The parent widget
 * @param	szName	The widget's name
 */
QueryPageBase::QueryPageBase(QWidget* pParent) :
	QWidget(pParent),
	m_bLocked(false)
{
}

/**
 * Class destructor.
 */
QueryPageBase::~QueryPageBase()
{
}

/**
 * Sets the list's colours and font, according the user's preferences.
 */
void QueryPageBase::applyPrefs()
{
    QPalette pe = m_pView->palette();
    pe.setColor(QPalette::Background, Config().getColor(KScopeConfig::QueryWindowBack));
    pe.setColor(QPalette::Foreground, Config().getColor(KScopeConfig::QueryWindowFore));
    m_pView->setPalette(pe);

	// Apply colour settings
	m_pView->setFont(Config().getFont(KScopeConfig::QueryWindow));
}

/**
 * Restores a locked query from the given query file.
 * NOTE: The query file is deleted when loading is complete.
 * @param	sProjPath	The full path of the project directory
 * @param	sFileName	The name of the query file to load
 * @return	true if successful, false otherwise
 */
bool QueryPageBase::load(const QString& sProjPath, const QString& sFileName, 
        const QString &srcRoot)
{
	QString sTemp, sFile, sFunc, sLine, sText;
	int nState;
	
	// Try to open the query file for reading
	QFile file(sProjPath + "/" + sFileName);
	if (!file.open(QIODevice::ReadOnly))
		return false;
	
	{
		// Use a new scope for the QTextStream object, to ensure its 
		// destruction before the file is deleted
		QTextStream str(&file);
		
		// Make sure the file's version is correct
		sTemp = str.readLine();
		if (sTemp != FILE_VERSION) {
			file.remove();
			return false;
		}

		// Try to read the file header
		if (!readHeader(str))
			return false;
		
		// Read query records
		sTemp = str.readLine();
		nState = 0;
		while (sTemp != QString::null) {
			switch (nState) {
			// File path
			case 0:
				sFile = sTemp;
                if (srcRoot != "/")
                    sFile.replace(srcRoot, "$");
				break;
				
			// Function name
			case 1:
				sFunc = sTemp;
				break;
				
			// Line number
			case 2:
				sLine = sTemp;
				break;
				
			// Text string
			case 3:
				sText = sTemp;
				addRecord(sFile, sFunc, sLine, sText);
				break;
			}
			
			nState = (nState + 1) % 4;
			sTemp = str.readLine();
		}
	}
	
	// Delete the query file
	file.remove();
	
	return true;
}

/**
 * Writes the contents of the page to a file.
 * This method is called for pages that shoukld be stored before the owner 
 * project is closed (@see shouldSave()).
 * @param	sProjPath	The full path of the project directory
 * @param	sFileName	Holds the file name to which the page was saved, upon
 *						return
 * @return	true if successful, false otherwise
 */
bool QueryPageBase::save(const QString& sProjPath, QString& sFileName)
{
	QTreeWidgetItemIterator itr(m_pView);

	// Get the file name to use
	sFileName = getFileName(sProjPath);
	if (sFileName.isEmpty())
		return false;
		
	// Open the query file for writing
	QFile file(sProjPath + "/" + sFileName);
	if (!file.open(QIODevice::WriteOnly))
		return false;
	
	QTextStream str(&file);
	
	// Write the version string
	str << FILE_VERSION << "\n";
	
	writeHeader(str);
		
	// Write all records
    for (; *itr; ++itr) {
		str << (*itr)->text(0) << "\n" 
			<< (*itr)->text(1) << "\n"
			<< (*itr)->text(2) << "\n"
			<< (*itr)->text(3) << "\n";
	}
	
	return true;
}

/**
 * Selects the next record in the view.
 */
void QueryPageBase::selectNext()
{
	m_pView->selectNext();
}

/**
 * Selects the previous record in the view.
 */
void QueryPageBase::selectPrev()
{
	m_pView->selectPrev();
}

#include "querypagebase.moc"
