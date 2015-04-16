#ifndef KSCOPEACTIONS_H
#define KSCOPEACTIONS_H

//#include <KLocale>
//#include <KStandardAction>
#include <KActionCollection>
#include <kaction.h>
#include <QList>
#include <ktoggleaction.h>

class KScope;

typedef QList<KAction *> ActionList;

/**
 * A helper class for managing KScope's menu commands.
 * @author	Elad Lahav
 */
class KScopeActions : public QObject
{
	Q_OBJECT
	
public:
	KScopeActions(KScope*);
	~KScopeActions();
	
	void init();
	void initPopups();
	void initLayoutActions();
	void enableExtEditor(bool);
	
	KToggleAction* getLockAction() { return m_pLockAction; }
	
public slots:
	void slotQueryDockToggled(bool);
	void slotQueryDockClosed();
	void slotFileViewDockClosed();
	void slotEnableProjectActions(bool);
	void slotEnableFileActions(bool);
	
signals:
	void toggleProject(bool bEnable);
	void toggleFile(bool bEnable);
	
private:
	KScope* m_pWindow;
	KActionCollection* m_pCollection;
	
	/** A list of actions that require an active project. */
	ActionList m_lstProjActions;
	
	/** A list of actions that require an active file. */
	ActionList m_lstFileActions;
	
	/** A toggle menu item for locking/unlocking query pages. */
	KToggleAction* m_pLockAction;

	/** The "Edit in External Editor" menu command. */
	KAction* m_pExtEditAction;
	
	/** The "Show/Hide File View" menu command. */
	KToggleAction* m_pToggleFileViewAction;
	
	/** The "Show/Hide Query Window" menu command. */
	KToggleAction* m_pToggleQueryWindowAction;
	
	/** The "Show/Hide Tag List" menu command. */
	KToggleAction* m_pToggleTagListAction;
	
	KAction* addAction(const QString&, const char*, const char*, QWidget*,
		const char*, const char*, const char*);
	KToggleAction* addToggle(const QString&, const char*, const char*,
		QWidget*, const char*, const char*, const char*);
};

#endif
