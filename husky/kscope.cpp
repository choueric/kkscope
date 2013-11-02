#include "kscope.h"
#include "husky.h"
#include "kscopeconfig.h"

#include <QStatusBar>

#include <KLocale>
#include <KStandardAction>
#include <KActionCollection>

KScope::KScope(QWidget* pParent, const char* szName)
    : KXmlGuiWindow(pParent)
{
    int nTime = 10; 

    dp("KScope Constructor\n");

    Config().load();

    setupActions();

    //setupGUI(ToolBar | Keys | StatusBar | Save);

	// Show a toolbar show/hide menu
	setStandardToolBarMenuEnabled(true);

	// Create the initial GUI (no active part)
    /*
	setXMLFile("kscopeui.rc");
	createShellGUI();
    */
    //setupGUI(Default, "kscopeui.rc");


	// Rebuild the project database after a certain time period has elapsed
	// since the last save
	connect(&m_timerRebuild, SIGNAL(timeout()), this, SLOT(slotRebuildDB()));

	// Reset the rebuild timer
	m_timerRebuild.start(nTime * 1000);

    Config().loadWorkspace(this);
}
 
void KScope::setupActions()
{
    KAction* clearAction = new KAction(this);
    clearAction->setText(i18n("&Clear"));
    clearAction->setIcon(KIcon("document-new"));
    actionCollection()->addAction("clear", clearAction);
    connect(clearAction, SIGNAL(triggered(bool)),
            this, SLOT(speak()));

    setupGUI(Default, "test.rc");
}

/**
 * Class destructor.
 */
KScope::~KScope()
{
    dp("Kscope Destructor\n");
    Config().store();
    Config().storeWorkspace(this);
}


void KScope::initMainWindow()
{
}

/**
 * Opens a project
 * If another project is currently active, it is closed first.
 * @param   sDir    The directory of the project to open.
 */
void KScope::openProject(const QString &sDir)
{
#if 0
    QString sPorjDir;
    ProjectBase *pProj;
    QStringList slQueryFiles;
    QStringList slCallTreeFiles;
    QStringList slArgs;
    ProjectBase::Options opt;
#endif
}


/**
 * Handles the "File->New" menu command.
 * Creates an editor page for a new unnamed file.
 */
void KScope::slotNewFile()
{
#if 0
	EditorPage* pPage;

	// Create the new editor page
	pPage = createEditorPage();
	
	// Mark the page as containing a new file
	pPage->setNewFile();
#endif
}


/**
 * Handles the "File->Open" menu command.
 * Prompts the user for a file name, and opens it in a new editor page.
 */
void KScope::slotOpenFile()
{
#if 0
	ProjectBase* pProj;
	QStringList slFiles;
	QStringList::Iterator itr;
	
	// Prompt the user for the file(s) to open.
	pProj = m_pProjMgr->curProject();
	slFiles = KFileDialog::getOpenFileNames(pProj ? pProj->getSourceRoot() : 
		QString::null);
	
	// Open all selected files.
	for (itr = slFiles.begin(); itr != slFiles.end(); ++itr) {
		if (!(*itr).isEmpty())
			slotShowEditor(*itr, 0);
	}
#endif
}

/**
 * Handles the "File->Close" menu command.
 * Closes the currently active editor page.
 */
void KScope::slotCloseEditor()
{
	//m_pEditTabs->removeCurrentPage();
}

/**
 * Handles the "Project->New..." command.
 * Prompts the user for the name and folder for the project, and then creates
 * the project.
 */
void KScope::slotCreateProject()
{
#if 0
	NewProjectDlg dlg(true, this);
	ProjectBase::Options opt;
	QString sProjPath;
	
	// Prompt the user to close any active projects
	if (m_pProjMgr->curProject()) {
		if (KMessageBox::questionYesNo(0, 
			i18n("The current project needs to be closed before a new one is"
			" created.\nWould you like to close it now?")) != 
			KMessageBox::Yes) {
			return;
		}
		
		// Try to close the project.
		if (!slotCloseProject())
			return;
	}
	
	// Display the "New Project" dialog
	if (dlg.exec() != QDialog::Accepted)
		return;

	// Create and open the new project
	dlg.getOptions(opt);
	if (m_pProjMgr->create(dlg.getName(), dlg.getPath(), opt, sProjPath))
		openProject(sProjPath);
#endif
}


/**
 * Handles the "Project->Open..." command.
 * Prompts the user for a project file ("cscope.proj"), and opens the
 * selected project.
 */
void KScope::slotOpenProject()
{
#if 0
	OpenProjectDlg dlg;
	QString sPath;
	
	if (dlg.exec() == QDialog::Rejected)
		return;

	sPath = dlg.getPath();
	
	// Check if the path refers to a permanent or temporary project
	if (QFileInfo(sPath).isDir())
		openProject(sPath);
	else
		openCscopeOut(sPath);
#endif
}

/**
 * Handles the "Project->Add/Remove Files..." command.
 * Opens the project's files dialog, which allows the user to add and remove
 * source files.
 */
void KScope::slotProjectFiles()
{
#if 0
	ProjectBase* pProj;
	
	// A project must be open
	pProj = m_pProjMgr->curProject();
	if (!pProj)
		return;

	// Cannot update the file list of a temporary project
	if (pProj->isTemporary()) {
		KMessageBox::error(0, i18n("The Add/Remove Files dialogue is not "
				"available for temporary projects."));
		return;
	}

	// Display the files dialog
	ProjectFilesDlg dlg((Project*)pProj, this);
	if (dlg.exec() != QDialog::Accepted)
		return;
	
	// Update the project's file list
	if (pProj->storeFileList(&dlg))
		slotProjectFilesChanged();
#endif
}

/**
 * Handles the "Project->Properties..." command.
 * Opens the project's properties dialog, which allows the user to change
 * some attributes of the current project.
 * source files.
 */
void KScope::slotProjectProps()
{
#if 0
	ProjectBase* pProj;
	ProjectBase::Options opt;
	
	// A project must be open
	pProj = m_pProjMgr->curProject();
	if (!pProj)
		return;

	// No properties for a temporary project
	if (pProj->isTemporary()) {
		KMessageBox::error(0, i18n("The Project Properties dialogue is not "
			"available for temporary projects."));
		return;
	}
	
	// Create the properties dialog
	NewProjectDlg dlg(false, this);
	pProj->getOptions(opt);
	dlg.setProperties(pProj->getName(), pProj->getPath(), opt);
		
	// Display the properties dialog
	if (dlg.exec() != QDialog::Accepted)
		return;

	// Set new properties
	dlg.getOptions(opt);
	pProj->setOptions(opt);
	
	// Reset the CscopeFrontend class and the builder object
	initCscope();
	
	// Set auto-completion parameters
	SymbolCompletion::initAutoCompletion(opt.bACEnabled, opt.nACMinChars,
		opt.nACDelay, opt.nACMaxEntries);
	
	// Set per-project command-line arguments for Ctags
	CtagsFrontend::setExtraArgs(opt.sCtagsCmd);
	
	// Set the source root
	m_pFileView->setRoot(pProj->getSourceRoot());
#endif
}

/**
 * Handles the "Cscope->Open Cscope.out..." menu command.
 * Prompts the user for a Cscope.out file, and, if successful, opens a new
 * session for working with this file.
 */
void KScope::slotProjectCscopeOut()
{
#if 0
	QString sFilePath;
	
	// Prompt for a Cscope.out file
	sFilePath = KFileDialog::getOpenFileName();
	if (sFilePath.isEmpty())
		return;

	// Open a temporary project
	openCscopeOut(sFilePath);	
#endif
}


/**
 * Closes the active project.
 * Closing a project involves closing all of the editor windows (prompting
 * the user for unsaved changes); terminating the Cscope process; and further
 * clean-up of the project's data.
 */
bool KScope::slotCloseProject()
{
#if 0
	ProjectBase* pProj;
	Project::Session sess;
	
	// Do nothing if no project is open
	pProj = m_pProjMgr->curProject();
	if (!pProj)
		return true;
	
	// Make sure all FileLocation objects are deleted
	sess.fllOpenFiles.setAutoDelete(true);
	sess.fllBookmarks.setAutoDelete(true);
	
	// Close all open editor pages
	if (m_pEditTabs->count() > 0) {
		// Save session information for persistent projects
		if (!pProj->isTemporary()) {
			sess.sLastFile = m_pEditTabs->getCurrentPage()->getFilePath();
			m_pEditTabs->getOpenFiles(sess.fllOpenFiles);
			m_pEditTabs->getBookmarks(sess.fllBookmarks);
		}
		
		if (!m_pEditTabs->removeAllPages())
			return false;
	}
	
	// Disable project-related actions
	m_pActions->slotEnableProjectActions(false);
	
	// Destroy the make dialogue
	if (m_pMakeDlg != NULL) {
		// Save session information for persistent projects
		if (!pProj->isTemporary()) {
			sess.sMakeCmd = m_pMakeDlg->getCommand();
			sess.sMakeRoot = m_pMakeDlg->getDir();
		}
		
		delete m_pMakeDlg;
		m_pMakeDlg = NULL;
	}
	
	// Save session information for persistent projects
	if (!pProj->isTemporary()) {
		m_pQueryWidget->savePages(pProj->getPath(), sess.slQueryFiles);
		m_pCallTreeMgr->saveOpenDialogs(pProj->getPath(), sess.slCallTreeFiles);
	}
		
	// Close all query pages and call trees
	m_pQueryWidget->slotCloseAll();
	m_pCallTreeMgr->closeAll();
	
	// Store session information for persistent projects
	if (!pProj->isTemporary())
		((Project*)pProj)->storeSession(sess);
	
	// Close the project in the project manager, and terminate the Cscope
	// process
	m_pProjMgr->close();
	delete m_pCscopeBuild;
	m_pCscopeBuild = NULL;
	setCaption(QString::null);

	// Clear the contents of the file list
	m_pFileView->clear();

	// Reset queried symbols history
	SymbolDlg::resetHistory();
	
    // Remove any remaining status bar messages
    statusBar()->message("");
    
	return true;
#endif
	return true;
}

/**
 * Handles the "Cscope->References..." menu command.
 * Prompts the user for a symbol name, and initiates a query to find all 
 * references to that symbol.
 */
void KScope::slotQueryReference()
{
#if 0
	slotQuery(SymbolDlg::Reference, true);
#endif
}

/**
 * Handles the "Cscope->Definition..." menu command.
 * Prompts the user for a symbol name, and initiates a query to find the 
 * global definition of that symbol.
 */
void KScope::slotQueryDefinition()
{
#if 0
	slotQuery(SymbolDlg::Definition, true);
#endif
}

/**
 * Handles the "Cscope->Called Functions..." menu command.
 * Prompts the user for a function name, and initiates a query to find all 
 * function calls from that function.
 */
void KScope::slotQueryCalled()
{
#if 0
	slotQuery(SymbolDlg::Called, true);
#endif
}

/**
 * Handles the "Cscope->Calling Functions..." menu command.
 * Prompts the user for a function name, and initiates a query to find all 
 * functions calling that function.
 */
void KScope::slotQueryCalling()
{
#if 0
	slotQuery(SymbolDlg::Calling, true);
#endif
}

/**
 * Handles the "Cscope->Find Text..." menu command.
 * Prompts the user for a string, and initiates a query to find all
occurances 
 * of that string.
 */
void KScope::slotQueryText()
{
#if 0
	slotQuery(SymbolDlg::Text, true);
#endif
}

/**
 * Handles the "Cscope->Find EGrep Pattern..." menu command.
 * Prompts the user for a regular expression, and initiates a query to find 
 * all strings matching that pattern.
 */
void KScope::slotQueryPattern()
{
#if 0
	slotQuery(SymbolDlg::Pattern, true);
#endif
}

/**
 * Handles the "Cscope->Find File..." menu command.
 * Prompts the user for a file name, and initiates a query to find all files
 * having that name.
 */
void KScope::slotQueryFile()
{
#if 0
	slotQuery(SymbolDlg::FileName, true);
#endif
}

/**
 * Handles the "Cscope->Find Including Files..." menu command.
 * Prompts the user for a file name, and initiates a query to find all files
 * having an '#include' directive to that file.
 */
void KScope::slotQueryIncluding()
{
#if 0
	slotQuery(SymbolDlg::Including, true);
#endif
}

/**
 * Handles the "Cscope->Quick Definition" menu command.
 * Initiates a query to find the global definition of the symbol currently
 * selected or under the cursor. The user is prompted only if no symbol can
 * be found.
 */
void KScope::slotQueryQuickDef()
{
#if 0
	QString sSymbol;
	QueryViewDlg* pDlg;
	uint nType;
	bool bCase;
	
	// Get the requested symbol and query type
	nType = SymbolDlg::Definition;
	if (!getSymbol(nType, sSymbol, bCase, false))
		return;
		
	// Create a modeless query view dialogue
	pDlg = new QueryViewDlg(QueryViewDlg::DestroyOnSelect, this);
	
	// Display a line when it is selected in the dialogue
	connect(pDlg, SIGNAL(lineRequested(const QString&, uint)), this,
		SLOT(slotShowEditor(const QString&, uint)));
		
	// Start the query
	pDlg->query(nType, sSymbol);
#endif
}

/**
 * Handles the "Cscope->Call Tree..." menu command.
 * Displays a tree of functions calling the requested function.
 */
void KScope::slotCallTree()
{
#if 0
	slotQuery(SymbolDlg::CallTree, true);
#endif
}

/**
 * Handles the "Cscope->Rebuild Database..." command.
 * Rebuilds Cscope's database for the current project.
 */
void KScope::slotRebuildDB()
{
#if 0
	ProjectBase* pProj;
	
	pProj = m_pProjMgr->curProject();
	if (!pProj)
		return;
	
	if (!pProj->dbExists()) {
		m_pProgressDlg = new ProgressDlg(i18n("KScope"), i18n("Please wait "
			"while KScope builds the database"), this);
		m_pProgressDlg->setAllowCancel(false);
		m_pProgressDlg->setValue(0);
	}
	
	m_pCscopeBuild->rebuild();
#endif
}

/**
 * Handles the "Go->Position History" menu command.
 * Ensures that the query window is visible, and selects the active history
 * page.
 */
void KScope::slotHistoryShow()
{
#if 0
	toggleQueryWindow(true);
	m_pQueryWidget->selectActiveHistory();
#endif
}

/**
 * Handles the "Settings->Configure Shortcuts..." command.
 * Displays the prferences dialog, which allows the user 
 * to change the shortcuts for KScope.
 */
void KScope::slotShortcuts()
{
#if 0
	KKeyDialog::configure(actionCollection(), this);
#endif
}

/**
 * Handles the "Settings->Configure KScope..." command.
 * Displays the prferences dialog, which allows the user to set different
 * configuration parameters for KScope.
 */
void KScope::slotConfigure()
{
#if 0
	PreferencesDlg dlg;

	// Apply the preferences if either the "Apply" or the "OK" buttons are
	// clicked
	connect(&dlg, SIGNAL(applyPref()), this, SLOT(slotApplyPref()));

	// Show the dialog
	if (dlg.exec() == QDialog::Accepted) {
		// Verify Cscope's installation
		verifyCscope();
	}
#endif
}

/**
 * Handles the "Window->Close All" menu command.
 * Closes all open editor pages.
 */
void KScope::slotCloseAllWindows()
{
#if 0
	m_bUpdateGUI = false;
	m_pEditTabs->removeAllPages();
	m_bUpdateGUI = true;
#endif
}

/**
 * Handles the "Edit->Edit in External Editor" menu command.
 * Invokes an external editor for the current file and line number.
 */
void KScope::slotExtEdit()
{
#if 0
	QString sCmdLine;
	KProcess proc;

	// Create the command line for the external editor	
	sCmdLine = Config().getExtEditor();
	sCmdLine.replace("%F", m_sCurFilePath);
	sCmdLine.replace("%L", QString::number(m_nCurLine));
	
	// Run the external editor
	proc.setUseShell(true);
	proc << sCmdLine;
	proc.start(KProcess::DontCare);
#endif
}

/**
 * Handles the "Edit->Complete Symbol" menu command.
 * Creates a list of possible completions for the symbol currently under the
 * cursor.
 */
void KScope::slotCompleteSymbol()
{
#if 0
	EditorPage* pPage;
	
	pPage = m_pEditTabs->getCurrentPage();
	if (pPage != NULL)
		pPage->slotCompleteSymbol();
#endif
}

/**
 * Handles the "Help->Show Welcome Message..." menu command.
 * Displays the "Welcome" dialogue.
 */
void KScope::slotShowWelcome()
{
#if 0
	WelcomeDlg dlg;
	dlg.exec();
#endif
}

/**
 * Handles the "Edit->Go To Tag" menu command.
 * Sets the cursor to the edit box of the current tag list.
 */
void KScope::slotGotoTag()
{
#if 0
	EditorPage* pPage;
	
	pPage = m_pEditTabs->getCurrentPage();
	if (pPage)
		pPage->setTagListFocus();
#endif
}

/**
 * Handles the "Project->Make..." menu command.
 * Displays the make dialogue.
 */
void KScope::slotProjectMake()
{
#if 0
	QString sCmd, sDir;
	
	// Create the make dialogue, if it does not exist
	if (m_pMakeDlg == NULL) {
		// Create the dialogue
		m_pMakeDlg = new MakeDlg();
		
		// Set make parameters for this project
		m_pProjMgr->curProject()->getMakeParams(sCmd, sDir);
		m_pMakeDlg->setCommand(sCmd);
		m_pMakeDlg->setDir(sDir);
		
		// Show the relevant source location when an error link is clicked
		connect(m_pMakeDlg, SIGNAL(fileRequested(const QString&, uint)), this,
			SLOT(slotShowEditor(const QString&, uint)));
		
		// Show the dialogue
		m_pMakeDlg->show();
	}
	else if (m_pMakeDlg->isShown()) {
		// The dialogue exists, and is visible, just raise it
		m_pMakeDlg->raise();
		m_pMakeDlg->setActiveWindow();
	}
	else {
		// The dialogue exists but is closed, show it
		m_pMakeDlg->show();
	}
#endif
}

/**
 * Handles the "Project->Remake..." menu command.
 * Displays the make dialogue and runs the make command.
 */
void KScope::slotProjectRemake()
{
#if 0
	// Make sure the make dialogue exists and is displayed
	slotProjectMake();
	
	// Run the make command
	m_pMakeDlg->slotMake();
#endif
}

/**
 * Handles the "Go->Global Bookmarks" menu command.
 * Displays a dialogue with the set of all bookmarks currently set in this
 * project.
 */
void KScope::slotShowBookmarks()
{
#if 0
	BookmarksDlg dlg;
	QString sPath;
	uint nLine;
	
	// Load the bookmark list
	m_pEditTabs->showBookmarks(dlg.getView());
	
	// Show the dialogue
	if (dlg.exec() != QDialog::Accepted)
		return;
	
	// Go to the selected bookmark
	dlg.getBookmark(sPath, nLine);
	slotShowEditor(sPath, nLine);
#endif
}

/**
 * Refreshes the file list when files are added to or removed from a project,
 * and rebuilds the Cscope database.
 * This slot is attached to the fileListChanged() signal emitted by 
 * the ProjectManager object.
 */
void KScope::slotProjectFilesChanged()
{
#if 0
	QStringList slArgs;
	
	// Refresh the file list
	m_pFileList->setUpdatesEnabled(false);
	m_pFileList->clear();
	m_pProjMgr->curProject()->loadFileList(m_pFileList);
	m_pFileList->setUpdatesEnabled(true);
	
	// Rebuild the symbol database
	if (isAutoRebuildEnabled())
		slotRebuildDB();
#endif
}

/**
 * Adds a list of files to the current project.
 * This slot is connected to the filesAdded() signal of the ProjectManager
 * object. Once files are added to the project, they are also added to the
 * file list, and the project's database is rebuilt.
 * @param	slFiles	The list of file paths added to the project
 */
void KScope::slotFilesAdded(const QStringList& slFiles)
{
#if 0
	QStringList::const_iterator itr;

	// Add the file paths to the project's file list
	for (itr = slFiles.begin(); itr != slFiles.end(); ++itr)
		m_pFileList->addItem(*itr);
	
	// Rebuild the database
	if (isAutoRebuildEnabled())
		slotRebuildDB();
#endif
}

/**
 * Promts the user for a symbol, an starts a new Cscope query.
 * @param	nType	The numeric query type code
 * @param	bPrompt	true to always prompt for a symbol, false to try to
 * 					obtain the symbol automatically
 */
void KScope::slotQuery(uint nType, bool bPrompt)
{
#if 0
	QString sSymbol;
	CallTreeDlg* pCallTreeDlg;
	bool bCase;
	
	// Get the requested symbol and query type
	if (!getSymbol(nType, sSymbol, bCase, bPrompt))
		return;
		
	if (nType == SymbolDlg::CallTree) {
		// Create and display a call tree dialogue
		pCallTreeDlg = m_pCallTreeMgr->addDialog();
		pCallTreeDlg->setRoot(sSymbol);
		pCallTreeDlg->show();
	}
	else {
		// Run the requested query
		nType = SymbolDlg::getQueryType(nType);
		m_pQueryWidget->initQuery(nType, sSymbol, bCase);
		
		// Ensure Query Window is visible
		toggleQueryWindow(true);	
	}
#endif
}

/**
 * Deletes an editor page after it has been removed.
 * The document object associated with the page is removed from the part 
 * manager, and the view object is removed from the GUI manager.
 * This slot is connected to the editorRemoved() signal of the EditorTabs 
 * object.
 * @param	pPage	The editor page to delete
 */
void KScope::slotDeleteEditor(EditorPage* pPage)
{
#if 0
	guiFactory()->removeClient(pPage->getView());
	m_pEditMgr->remove(pPage->getDocument());
	delete pPage;
#endif
}

/**
 * Sets an editor part as active when its owner tab is chosen.
 * Whenever a different editor tab is chosen, its editor part should become
 * the active part. This means that this part's GUI is merged with the
 * application's, and that it responds to actions.
 * @param	pOldPage	The editor page that has ceased to be active
 * @param	pNewPage	The newly chosen editor page
 */
void KScope::slotChangeEditor(EditorPage* pOldPage, EditorPage* pNewPage)
{
#if 0
	KXMLGUIFactory* pFactory = guiFactory();
	
	// Remove the current GUI
	if (pOldPage)
		pFactory->removeClient(pOldPage->getView());

	// Set the new active part and create its GUI
	if (m_bUpdateGUI && pNewPage) {
		m_pEditMgr->setActivePart(pNewPage->getDocument());
		pFactory->addClient(pNewPage->getView());
		m_sCurFilePath = pNewPage->getFilePath();
		setCaption(m_pProjMgr->getProjName() + " - " + m_sCurFilePath);
	}
	
	// Enable/disable file-related actions, if necessary
	if (pOldPage && !pNewPage)
		m_pActions->slotEnableFileActions(false);
	else if (!pOldPage && pNewPage)
		m_pActions->slotEnableFileActions(true);
#endif
}

/**
 * Opens an editor for the given file and sets the cursor to the beginning of 
 * the requested line.
 * @param	sFilePath	The full path of the file to open for editing
 * @param	nLine		The number of the line on which to position the
 *						cursor, or 0 to maintain the cursor in its current
 *						position (which does not affect the position history)
 */
void KScope::slotShowEditor(const QString& sFilePath, uint nLine)
{
#if 0
	EditorPage* pPage;

	// Save current position in the position history
	if (nLine != 0 && (pPage = m_pEditTabs->getCurrentPage())) {
		m_pQueryWidget->addHistoryRecord(m_sCurFilePath, m_nCurLine,
			pPage->getLineContents(m_nCurLine));
	}
	
	// Open the requested file (or select an already-open editor page)
	pPage = addEditor(sFilePath);
	if (pPage == NULL)
		return;
	
	// Make sure the main window is visible
	raise();
	setWindowState(windowState() & ~WindowMinimized | WindowActive);
	
	if (nLine != 0) {
		// Set the cursor to the requested line
		pPage->slotGotoLine(nLine);
	
		// Add the new position to the position history
		m_pQueryWidget->addHistoryRecord(m_sCurFilePath, m_nCurLine,
			pPage->getLineContents(m_nCurLine));
	}
#endif
}

/**
 * Stores the path of a newly opened file.
 * This slot is connected to the fileOpened() signal emitted by an
 * EditorPage object.
 * @param	sFilePath	The full path of the opened file
 */
void KScope::slotFileOpened(EditorPage*, const QString& sFilePath)
{
#if 0
	m_sCurFilePath = sFilePath;
	setCaption(m_pProjMgr->getProjName() + " - " + m_sCurFilePath);
#endif
}

/**
 * Sets a timer for rebuilding the database after a file has been saved.
 * This slot is connected to the fileSaved() signal emitted by an EditorPage
 * object.
 * The time period before rebuilding is determined on a per-project basis.
 * @param	sPath	The full path of the modified file that caused this event
 * @param	bIsNew	true if this is a new file, false otherwise
 */
void KScope::slotFileSaved(const QString& sPath, bool bIsNew)
{
#if 0
	ProjectBase* pProj;
	int nTime;
	
	pProj = m_pProjMgr->curProject();
	if (!pProj)
		return;
	
	// Prompt the user to add this file to the current project
	if (bIsNew && !pProj->isTemporary()) {
		if (KMessageBox::questionYesNo(0, 
			i18n("Whould you like to add this file to the active project?")) == 
				  KMessageBox::Yes) {
			
			// Add the path to the 'cscope.files' file
			if (!((Project*)pProj)->addFile(sPath)) {
				KMessageBox::error(0, i18n("Failed to write the file list."));
				return;
			}
			
			// Add the path to the file list widget
			m_pFileList->addItem(sPath);
			
			// Rebuild immediately
			slotRebuildDB();
			return;
		}
	}
	
	// Get the project's auto-rebuild time
	nTime = pProj->getAutoRebuildTime();
	
	// Do nothing if the time is set to -1
	if (nTime == -1)
		return;
		
	// Check if the file is included in the project (external files should
	// not trigger the timer)
	if (!m_pFileList->findFile(sPath))
		return;
	
	// Rebuild immediately for a time set to 0
	if (nTime == 0) {
		slotRebuildDB();
		return;
	}

	// Reset the rebuild timer
	m_timerRebuild.start(nTime * 1000, true);
#endif
}

/**
 * Displays error messages from a Cscope process.
 * This slot is connected to the progress() signal emitted by the any
 * Cscope process.
 * @param	sMsg	The error message
 */
void KScope::slotCscopeError(const QString& sMsg)
{
#if 0
	m_pMsgDlg->addText(sMsg);
#endif
}

/**
 * Reports progress information from the Cscope process responsible for
 * rebuilding the cross-reference database.
 * This slot is connected to the progress() signal emitted by the builder
 * process.
 * Progress information is displayed in the status bar.
 * @param	nFiles	The number of files scanned
 * @param	nTotal	The total number of files in the project
 */
void KScope::slotBuildProgress(int nFiles, int nTotal)
{
#if 0
	QString sMsg;
	
	// Use the progress dialogue, if it exists (first time builds)
	if (m_pProgressDlg) {
		m_pProgressDlg->setValue((nFiles * 100) / nTotal);
		return;
	}
	
	// Show progress information
	sMsg = i18n("Rebuilding the cross reference database...") + " " +
		QString::number((nFiles * 100) / nTotal) + "%";
	statusBar()->message(sMsg);
#endif
}

/**
 * Reports to the user that Cscope has started building the inverted index.
 * This slot is connected to the buildInvIndex() signal emitted by the 
 * builder process.
 */
void KScope::slotBuildInvIndex()
{
#if 0
	if (m_pProgressDlg) {
		m_pProgressDlg->setLabel(i18n("Please wait while KScope builds the "
			"inverted index"));
		m_pProgressDlg->setIdle();
		return;
	}
	
	statusBar()->message(i18n("Rebuilding inverted index..."));
#endif
}

/**
 * Informs the user the database rebuild process has finished.
 * This slot is connected to the finished() signal emitted by the builder
 * process.
 */
void KScope::slotBuildFinished(uint)
{
#if 0
	// Delete the progress dialogue, if it exists (first time builds)
	if (m_pProgressDlg) {
		delete m_pProgressDlg;
		m_pProgressDlg = NULL;
		return;
	}
	
	// Show a message in the status bar
	statusBar()->message(i18n("Rebuilding the cross reference database..."
		"Done!"), 3000);
#endif
}

/**
 * Called if the build process failed to complete.
 * This slot is connected to the aborted() signal emitted by the builder
 * process.
 */
void KScope::slotBuildAborted()
{
#if 0
	// Delete the progress dialogue, if it exists (first time builds)
	if (m_pProgressDlg) {
		delete m_pProgressDlg;
		m_pProgressDlg = NULL;
	
		// Display a failure message
		KMessageBox::error(0, i18n("The database could not be built.\n"
			"Cross-reference information will not be available for this "
			"project.\n"
			"Please ensure that the Cscope parameters were correctly "
			"entered in the \"Settings\" dialogue."));		
		return;
	}
	
	// Show a message in the status bar
	statusBar()->message(i18n("Rebuilding the cross reference database..."
		"Failed"), 3000);	
#endif
}

/**
 * Applies the selected user preferences once the "Apply" or "OK" buttons in
 * the preferences dialog is clicked.
 */
void KScope::slotApplyPref()
{
#if 0
	m_pQueryWidget->applyPrefs();
	m_pFileList->applyPrefs();
	m_pEditTabs->applyPrefs();
	m_pEditMgr->applyPrefs();

	// Enable/disable the external editor menu item
	m_pActions->enableExtEditor(Config().useExtEditor());
#endif
}

/**
 * Displays the current cursor position, whenever it is moved by the user.
 * This slot is connected to the cursorPosChanged() signal emitted by an
 * EditorPage object.
 * @param	nLine	The new line number
 * @param	nCol	The new column number
 */
void KScope::slotShowCursorPos(uint nLine, uint nCol)
{
#if 0
	KStatusBar* pStatus = statusBar();
	QString sText;
	
	/* Show the line and column numbers. */
	QTextOStream(&sText) << " Line: " << nLine << " Col: " << nCol << " ";
	pStatus->changeItem(sText, 0);
	
	/* Store the current line. */
	m_nCurLine = nLine;
#endif
}

/**
 * A wrapper around slotShowEditor, that enables auto-hiding of the query
 * widget after a query result has been chosen.
 * This slot is connected to the lineRequested() signal emitted by a QueryPage
 * object.
 * @param	sFilePath	The full path of the file to open for editing
 * @param	nLine		The number of the line on which to position the cursor
 */
void KScope::slotQueryShowEditor(const QString& sFilePath, uint nLine)
{
#if 0
	// Hide the query window, if it was hidden before a query was initiated
	if (m_bHideQueryOnSelection)
		toggleQueryWindow(false);
	
	// Open an editor at the requested line
	slotShowEditor(sFilePath, nLine);
#endif
}

/**
 * Handles file drops inside the editors tab widget.
 * Opens all files dropped over the widget.
 * @param	pEvent	Pointer to an object containing the list of dropped files
 */
void KScope::slotDropEvent(QDropEvent* pEvent)
{
#if 0
	KURL::List list;
	KURL::List::Iterator itr;
		
	// Create a list of file URLs
	if (!KURLDrag::decode(pEvent, list))
		return;
		
	// Open all files in the list
	for (itr = list.begin(); itr != list.end(); ++itr)
		addEditor((*itr).path());
#endif
}

/**
 * Reports the results of the Cscope verification script.
 * This slot is connected to the done() signal emitted by the CscopeVerifier
 * object constructed in verifyCscope().
 */
void KScope::slotCscopeVerified(bool bResult, uint nArgs)
{
#if 0
	statusBar()->message(i18n("Verifying Cscope installation...Done"), 3000);
	
	// Mark the flag even if Cscope was not found, to avoid nagging the user
	// (who may wish to use KScope even with Cscope disabled)
	m_bCscopeVerified = true;

	// Prompt the user in case Cscope is not properly installed
	if (!bResult) {
		KMessageBox::error(0, i18n("Cscope may not be properly installed on "
			"this system.\nPlease check the Cscope path specified in KScope's "
			"configuration dialogue."));
		slotConfigure();
		return;
	}
		
	// Set the discoverred supported command-line arguments
	CscopeFrontend::setSupArgs(nArgs);
	
	// Build the database, if required
	if (m_bRebuildDB) {
		m_bRebuildDB = false;
		slotRebuildDB();
	}
#endif
}
