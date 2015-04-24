#include <klocale.h>
#include <kstandardaction.h>
#include <KActionCollection>

#include "kscopeactions.h"
#include "kscope.h"
#include "kscopeconfig.h"

KScopeActions::KScopeActions(KScope* pWindow) : QObject(),
		m_pWindow(pWindow),
		m_pCollection(pWindow->actionCollection())
{
}

KScopeActions::~KScopeActions()
{
}

/**
 * setupActions
 * Connects menu bar and toolbar commands with class members. These members
 * handle the actions associated with each command.
 */
// TODO: some Icon names are no longer valid.
// see /usr/share/icon
void KScopeActions::init()
{
	// File menu
	KStandardAction::openNew(m_pWindow, SLOT(slotNewFile()), m_pCollection);
	KStandardAction::open(m_pWindow, SLOT(slotOpenFile()), m_pCollection);
	KStandardAction::close(m_pWindow, SLOT(slotCloseEditor()), m_pCollection);
	KStandardAction::quit(m_pWindow, SLOT(slotClose()), m_pCollection);

	addAction(i18n("Go to File List"), NULL, "Ctrl+Shift+O",
		(QWidget *)m_pWindow->m_pFileList, SLOT(slotSetFocus()),
		"file_open_file_from_list", SIGNAL(toggleProject(bool)));
	
	addAction(i18n("Save Al&l"), "save_all", "Ctrl+L",
		(QWidget *)m_pWindow->m_pEditTabs,
		SLOT(slotSaveAll()), "file_save_all", NULL);
	
	// Edit menu
	m_pExtEditAction = addAction(i18n("Edit in E&xternal Editor"),
		"accessories-text-editor", "Ctrl+E", m_pWindow, SLOT(slotExtEdit()),
		"edit_external_editor", SIGNAL(toggleFile(bool))); // renew
		
	addAction(i18n("Go To Tag"),
		"go-jump-definition", "Ctrl+Shift+T", m_pWindow, SLOT(slotGotoTag()),
		"edit_goto_tag", SIGNAL(toggleFile(bool))); // renew
	
	addAction(i18n("Complete Symbol"),
		"task-complete", "Ctrl+Space", m_pWindow, SLOT(slotCompleteSymbol()),
		"edit_comp_symbol", SIGNAL(toggleFile(bool))); // renew

	// View menu
	m_pToggleTagListAction = addToggle(i18n("Toggle Tag List"),
		"view-list-details", "Ctrl+'", (QWidget *)m_pWindow->m_pEditTabs,
		SLOT(slotToggleTagList()), "view_toggle_tag_list", NULL); // renew

	m_pToggleQueryWindowAction = addToggle(i18n("Toggle Query Window"),
		"view-split-top-bottom", "Ctrl+.", m_pWindow,
		SLOT(slotChangeSHowStateQueryDock()), "view_toggle_query_dock", NULL); // renew

	m_pToggleFileViewAction = addToggle(i18n("Toggle File List"),
		"view-sidetree", "Ctrl+/", m_pWindow,
		SLOT(slotChangeShowStateFileViewDock()), "view_toggle_filelist_dock", NULL); // renew

	// Project menu
	addAction(i18n("&New Project..."), "project-development-new-template", NULL, m_pWindow,
		SLOT(slotCreateProject()), "project_new", NULL); // renew
		
	addAction(i18n("&Open Project..."), "project-open", NULL,
		m_pWindow, SLOT(slotOpenProject()), "project_open", NULL);  // renew
		
	addAction(i18n("Open &Cscope.out..."), NULL, NULL, m_pWindow,
		SLOT(slotProjectCscopeOut()), "project_cscope_out", NULL);  // used
		
	addAction(i18n("Add/Remove &Files..."), NULL, NULL, m_pWindow,
		SLOT(slotProjectFiles()), "project_add_rem_files",
		SIGNAL(toggleProject(bool)));  // used
		
	addAction(i18n("&Properties..."), "preferences-system", NULL, m_pWindow,
		SLOT(slotProjectProps()), "project_properties",
		SIGNAL(toggleProject(bool)));  // renew
		
	addAction(i18n("&Make Project"), "run-build", "Ctrl+M",
		m_pWindow, SLOT(slotProjectMake()), "project_make",
		SIGNAL(toggleProject(bool)));  // renew
		
	addAction(i18n("&Remake Project"), "run-build-clean", "Ctrl+Shift+M",
		m_pWindow, SLOT(slotProjectRemake()), "project_remake",
		SIGNAL(toggleProject(bool)));  // renew
	
	addAction(i18n("&Close Project"), "window-close", NULL, m_pWindow,
		SLOT(slotCloseProject()), "project_close",
		SIGNAL(toggleProject(bool)));  // renew

	// Cscope menu
	addAction(i18n("Re&build database"), "vcs-update-cvs-cervisia", NULL, m_pWindow,
		SLOT(slotRebuildDB()), "cscope_rebuild",
		SIGNAL(toggleProject(bool))); // renew
		
	addAction(i18n("&References..."), NULL, "Ctrl+0", m_pWindow,
		SLOT(slotQueryReference()), "cscope_references",
		SIGNAL(toggleProject(bool))); // used
		
	addAction(i18n("&Definition..."), NULL, "Ctrl+1", m_pWindow,
		SLOT(slotQueryDefinition()), "cscope_definition",
		SIGNAL(toggleProject(bool))); // used
	
	addAction(i18n("&Called Functions..."), NULL, "Ctrl+2", m_pWindow,
		SLOT(slotQueryCalled()), "cscope_called",
		SIGNAL(toggleProject(bool))); // used
		
	addAction(i18n("C&alling Functions..."), NULL, "Ctrl+3", m_pWindow,
		SLOT(slotQueryCalling()), "cscope_calling",
		SIGNAL(toggleProject(bool))); // used
		
	addAction(i18n("Find &Text..."), NULL, "Ctrl+4", m_pWindow,
		SLOT(slotQueryText()), "cscope_text",
		SIGNAL(toggleProject(bool))); // used
		
	addAction(i18n("Find &EGrep Pattern..."), NULL, "Ctrl+5", m_pWindow,
		SLOT(slotQueryPattern()), "cscope_pattern",
		SIGNAL(toggleProject(bool))); // used
		
	addAction(i18n("Find &File..."), NULL, "Ctrl+7", m_pWindow,
		SLOT(slotQueryFile()), "cscope_file",
		SIGNAL(toggleProject(bool))); // used
		
	addAction(i18n("&Including Files..."), NULL, "Ctrl+8", m_pWindow,
		SLOT(slotQueryIncluding()), "cscope_including",
		SIGNAL(toggleProject(bool))); // used
		
	addAction(i18n("&Quick Definition"), NULL, "Ctrl+]", m_pWindow,
		SLOT(slotQueryQuickDef()), "cscope_quick_def",
		SIGNAL(toggleProject(bool))); // used
		
	addAction(i18n("Call &Graph..."), NULL, "Ctrl+\\", m_pWindow,
		SLOT(slotCallTree()), "cscope_call_tree",
		SIGNAL(toggleProject(bool))); // used

	// Go menu
	addAction(i18n("P&revious Result"), "draw-arrow-up", "Alt+Up", 
		(QWidget *)m_pWindow->m_pQueryWidget,
		SLOT(slotPrevResult()), "go_prev_result",
		SIGNAL(toggleProject(bool)));  // renew
	
	addAction(i18n("N&ext Result"), "draw-arrow-down", "Alt+Down",
		(QWidget *)m_pWindow->m_pQueryWidget,
		SLOT(slotNextResult()), "go_next_result",
		SIGNAL(toggleProject(bool)));  // renew
	
	addAction(i18n("&Previous Position"), "draw-arrow-back", "Alt+Left",
		(QWidget *)m_pWindow->m_pQueryWidget,
		SLOT(slotHistoryPrev()), "go_prev_pos", NULL);  // renew
	
	addAction(i18n("&Next Position"), "draw-arrow-forward", "Alt+Right",
		(QWidget *)m_pWindow->m_pQueryWidget,
		SLOT(slotHistoryNext()), "go_next_pos", NULL);  // renew
		
	addAction(i18n("Position &History"), "view-history", "Ctrl+h",
		m_pWindow, SLOT(slotHistoryShow()), "go_history", NULL);  // renew
		
	addAction(i18n("Global &Bookmarks"), "bookmark-toolbar", "Ctrl+Shift+G",
		m_pWindow, SLOT(slotShowBookmarks()), "go_bookmarks", NULL);  // renew

	// Window menu
	addAction(i18n("Close &All"), "window-close", NULL, m_pWindow,
		SLOT(slotCloseAllWindows()), "window_close_all", NULL); // renew
		
	addAction(i18n("Go &Left"), "draw-arrow-back", "Alt+Shift+Left",
		(QWidget *)m_pWindow->m_pEditTabs, SLOT(slotGoLeft()),
		"window_go_left", NULL); // renew
		
	addAction(i18n("Go &Right"), "draw-arrow-forward", "Alt+Shift+Right",
		(QWidget *)m_pWindow->m_pEditTabs,
		SLOT(slotGoRight()), "window_go_right", NULL); // renew
		
	// Settings menu
	KStandardAction::preferences(m_pWindow, SLOT(slotConfigure()), m_pCollection);
	KStandardAction::keyBindings(m_pWindow, SLOT(slotShortcuts()), m_pCollection);
	
	// Help menu
	addAction(i18n("Show &Welcome Message..."), NULL, NULL,
		m_pWindow, SLOT(slotShowWelcome()), "help_welcome", NULL);  //used
	
	// Query widget popup menu
	addAction(i18n("&New query"), "tab-new", NULL,
		(QWidget *)m_pWindow->m_pQueryWidget,
		SLOT(slotNewQueryPage()),
		"query_new", SIGNAL(toggleProject(bool))); // renew
	
	addAction(i18n("&Refresh query"), "view-refresh", NULL,
		(QWidget *)m_pWindow->m_pQueryWidget,
		SLOT(slotRefreshCurrent()),
		"query_refresh", SIGNAL(toggleProject(bool))); // renew
		
	m_pLockAction = addToggle(i18n("&Lock/Unlock query"), "object-locked",
		NULL, (QWidget *)m_pWindow->m_pQueryWidget,
		SLOT(slotLockCurrent()), "query_toggle_locked",
		SIGNAL(toggleProject(bool))); // renew
		
	addAction(i18n("&Close query"), "tab-close", NULL,
		(QWidget *)m_pWindow->m_pQueryWidget,
		SLOT(slotCloseCurrent()), "query_close",
		SIGNAL(toggleProject(bool))); // renew
	
	m_pExtEditAction->setEnabled(Config().useExtEditor());
}

void KScopeActions::initLayoutActions()
{
	m_pToggleFileViewAction->setChecked(!(m_pWindow->m_pFileViewDock->isHidden()));
	m_pToggleQueryWindowAction->setChecked(!(m_pWindow->m_pQueryDock->isHidden()));
	m_pToggleTagListAction->setChecked(Config().getShowTagList());
}

/**
 * Enables/disables the "Edit in External Editor" command.
 * @param	bEnable	true to enable the command, false to disable it
 */
void KScopeActions::enableExtEditor(bool bEnable)
{
	m_pExtEditAction->setEnabled(bEnable);
}
 
void KScopeActions::slotQueryDockToggled(bool bVisible)
{
	m_pToggleQueryWindowAction->setChecked(bVisible);
}

/**
 * Enables/disables all actions related to open projects.
 * This slot should be called whenever a project is opened or closed.
 * @param	bEnable	true to enable actions, false to disable
 */
void KScopeActions::slotEnableProjectActions(bool bEnable)
{
	emit toggleProject(bEnable);
}
 
/**
 * Enables/disables all actions related to open files.
 * This slot should be called the first file is opened, or when the last one
 * is closed.
 * @param	bEnable	true to enable actions, false to disable
 */
void KScopeActions::slotEnableFileActions(bool bEnable)
{
	emit toggleFile(bEnable);
}

/**
 * Creates a new action.
 * @param	sCaption	The text to display in the menu item
 * @param	szIcon		Optional icon associated with the action
 * @param	szShortcut	Optional key-combination string
 * @param	pReceiver	The widget to receive the action's signal
 * @param	szSlot		The widget's slot that connect to the signal
 * @param	szName		The XML entry corresponding to the action
 * @param	szSignal	Optional signal to connect to the setEnabled() slot of
 *						the action
 * @return	The newly created action object
 */
KAction* KScopeActions::addAction(const QString& sCaption, const char* szIcon,
	const char* szShortcut, QWidget* pReceiver, const char* szSlot,
	const char* szName, const char* szSignal)
{
	KAction* pAction = NULL;

    pAction = new KAction(m_pWindow);
    pAction->setText(sCaption); // show in the toolbar
    pAction->setHelpText(sCaption); // show in the toolbar
    if (szIcon)
        pAction->setIcon(KIcon(szIcon));
    pAction->setShortcut(szShortcut == NULL ? KShortcut(): KShortcut(szShortcut));
    m_pCollection->addAction(szName, pAction);
    connect(pAction, SIGNAL(triggered(bool)), pReceiver, szSlot);

	// Add to the given action list, if any
	if (szSignal)
		connect(this, szSignal, pAction, SLOT(setEnabled(bool)));

	return pAction;
}

/**
 * Creates a new toggle action.
 * @param	sCaption	The text to display in the menu item
 * @param	szIcon		Optional icon associated with the action
 * @param	szShortcut	Optional key-combination string
 * @param	pReceiver	The widget to receive the action's signal
 * @param	szSlot		The widget's slot that connect to the signal
 * @param	szName		The XML entry corresponding to the action
 * @param	szSignal	Optional signal to connect to the setEnabled() slot of
 *						the action
 * @return	The newly created action object
 */
KToggleAction* KScopeActions::addToggle(const QString& sCaption,
	const char* szIcon, const char* szShortcut, QWidget* pReceiver,
	const char* szSlot, const char* szName, const char* szSignal)
{
	KToggleAction* pAction = NULL;

    pAction = new KToggleAction(m_pWindow);
    pAction->setText(sCaption);
    pAction->setHelpText(sCaption); // show in the toolbar
    if (szIcon)
        pAction->setIcon(KIcon(szIcon));
    pAction->setShortcut(szShortcut == NULL ? KShortcut(): KShortcut(szShortcut));
    m_pCollection->addAction(szName, pAction);
    connect(pAction, SIGNAL(triggered()), pReceiver, szSlot);

	// Add to the given action list, if any
	if (szSignal)
		connect(this, szSignal, pAction, SLOT(setEnabled(bool)));

	return pAction;
}

#include "kscopeactions.moc"
