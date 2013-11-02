#ifndef KSCOPE_H
#define KSCOPE_H

#include <QtGui>
#include <QTimer>
#include <kparts/mainwindow.h>
#include <KXmlGuiWindow>

class EditorPage;
class FileList;

class KScope : public KXmlGuiWindow
{
	Q_OBJECT

public:
	KScope(QWidget *pParent = 0, const char *szName = 0);
	~KScope();

    void openProject(const QString &);

private:
    QTimer m_timerRebuild;

	/** Pointer to the file list part of the FileView widget. */
	FileList* m_pFileList;

    void initMainWindow();
    void setupActions();


private slots:
	// Menu actions
	void slotNewFile();
	void slotOpenFile();
	void slotCloseEditor();
	void slotCreateProject();
	void slotOpenProject();
	void slotProjectFiles();
	void slotProjectProps();
	void slotProjectCscopeOut();
	bool slotCloseProject();
	void slotQueryReference();
	void slotQueryDefinition();
	void slotQueryCalled();
	void slotQueryCalling();
	void slotQueryText();
	void slotQueryPattern();
	void slotQueryFile();
	void slotQueryIncluding();
	void slotQueryQuickDef();
	void slotCallTree();
	void slotRebuildDB();
	void slotHistoryShow();
	void slotShortcuts();
	void slotConfigure();
	void slotCloseAllWindows();
	void slotExtEdit();
	void slotCompleteSymbol();
	void slotShowWelcome();
	void slotGotoTag();
	void slotProjectMake();
	void slotProjectRemake();
	void slotShowBookmarks();
	
	// Other slots
	void slotProjectFilesChanged();
	void slotFilesAdded(const QStringList&);
	void slotQuery(uint, bool);
	void slotDeleteEditor(EditorPage*);
	void slotChangeEditor(EditorPage*, EditorPage*);
	void slotShowEditor(const QString&, uint);
	void slotFileOpened(EditorPage*, const QString&);
	void slotFileSaved(const QString&, bool);
	void slotCscopeError(const QString&);
	void slotBuildProgress(int, int);
	void slotBuildInvIndex();
	void slotBuildFinished(uint);
	void slotBuildAborted();
	void slotApplyPref();
	void slotShowCursorPos(uint, uint);
	void slotQueryShowEditor(const QString&, uint);
	void slotDropEvent(QDropEvent*);
	void slotCscopeVerified(bool, uint);

    // for test
    void speak() { printf("speak\n"); };

};

#endif
