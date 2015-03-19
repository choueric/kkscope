#include <klocale.h>
#include "queryviewdriver.h"
#include "queryview.h"

/**
 * Class constructor.
 * Creates a driver that adds new records as root items in the given view.
 * @param	pView	The view to which this driver should add records
 * @param	pParent	The parent object of the driver
 * @param	szName	The name of the object
 */
QueryViewDriver::QueryViewDriver(QueryView* pView, QObject* pParent, 
	const char* szName) : QObject(pParent),
	m_pView(pView),
	m_pItem(NULL),
	m_progress(pView),
	m_bRunning(false)
{
	m_pCscope = new CscopeFrontend();	
		
	// Add records to the page when Cscope outputs them
	connect(m_pCscope, SIGNAL(dataReady(FrontendToken*)), this,
		SLOT(slotDataReady(FrontendToken*)));
		
	// Report progress information
	connect(m_pCscope, SIGNAL(progress(int, int)), this,
		SLOT(slotProgress(int, int)));

	// Perform tasks when the query process terminates
	connect(m_pCscope, SIGNAL(finished(uint)), this,
		SLOT(slotFinished(uint)));
	
	connect(m_pView, SIGNAL(destroyed()), this, SLOT(slotViewClosed()));
}

/**
 * Class destructor.
 */
QueryViewDriver::~QueryViewDriver()
{
	//delete m_pCscope;
}

/**
 * Executes a query.
 * @param	nType	The type of the query (@see CscopeFrontend)
 * @param	sText	The query's text
 * @param	bCase		true for case-sensitive queries, false otherwise
 * @param	pItem	If non-null, represents an view item passed back to
 *					the view in a call to addRecord()
 */
void QueryViewDriver::query(uint nType, const QString& sText, bool bCase,
	QTreeWidgetItem* pItem)
{
	m_pItem = pItem;
	
	// Make sure sorting is disabled while entries are added
	m_pView->setSortingEnabled(false);
		
	// Execute the query
	m_pCscope->query(nType, sText, bCase);
	m_bRunning = true;
	m_pView->setEnabled(false);
	m_pView->setUpdatesEnabled(false);
}

/**
 * Adds a query entry to the view.
 * Called by a CscopeFrontend object, when a new entry was received in its
 * whole from the Cscope back-end process.
 * @param	pToken	The first token in the entry
 */
void QueryViewDriver::slotDataReady(FrontendToken* pToken)
{
	QString sFile, sFunc, sLine, sText;
	
	// Get the file name
	sFile = pToken->getData();
	pToken = pToken->getNext();

	// Get the function name
	sFunc = pToken->getData();
	pToken = pToken->getNext();

	// Get the line number
	sLine = pToken->getData();
	if (!sLine.toInt()) {
		// Line number could not be 0!
		// means that function name was empty
		sLine = sFunc;
		sFunc = "<global>";
	}
	else {
		pToken = pToken->getNext();
	}
	
	// Get the line's text
	sText = pToken->getData();
	pToken = pToken->getNext();

	// Add a new item at the end of the list
	m_pView->addRecord(sFunc, sFile, sLine, sText, m_pItem);
}

/**
 * Handles a finished query event, reported by the Cscope frontend object.
 * If no resutls are available, a proper message is displayed. If only one 
 * record was generated by Cscope, it is automatically selected for viewing.
 * @param	nRecords	The number of records the query has generated
 */
void QueryViewDriver::slotFinished(uint nRecords)
{
	// The query is no longer running
	m_bRunning = false;
	m_pView->setEnabled(true);
	m_pView->setUpdatesEnabled(true);
	//m_pView->triggerUpdate();
	
	// Destroy the progress bar
	m_progress.finished();

	// Let owner widget decide what to do based on the number of records
	m_pView->queryFinished(nRecords, m_pItem);
}

/**
 * Displays search progress information.
 * This slot is connected to the progress() signal emitted by a
 * CscopeFrontend object.
 * @param	nFiles	The number of files scanned
 * @param	nTotal	The total number of files in the project
 */
void QueryViewDriver::slotProgress(int nFiles, int nTotal)
{
	// A progress report is available, instruct the owner object to show the
	// view
	if (nTotal > 1)
		m_pView->queryProgress();
		
	// Set the progress bar
	m_progress.setProgress(nFiles, nTotal);
}

/**
 * Called when the owner view is destroyed.
 */
void QueryViewDriver::slotViewClosed()
{
	m_pView = NULL;
	m_pCscope->kill();
}

#include "queryviewdriver.moc"
