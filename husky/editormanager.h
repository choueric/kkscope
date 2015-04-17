#ifndef EDITORMANAGER_H
#define EDITORMANAGER_H

#include <qwidget.h>
#include <kparts/partmanager.h>
#include <klibloader.h>
#include <ktexteditor/document.h>

/**
 * Creates text editor parts, used to open source files.
 * The EditorManager is responsible for creating parts, and managing their
 * GUI integration.
 * @author Elad Lahav
 */

class EditorManager : public KParts::PartManager
{
   Q_OBJECT

public: 
	EditorManager(QWidget* pParent = 0);
	~EditorManager();

	KTextEditor::Document* add();
	void remove(KTextEditor::Document*);
	void applyPrefs();

private:
    KTextEditor::Editor* m_pEditor;
};

#endif
