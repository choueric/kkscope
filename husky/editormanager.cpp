#include <KApplication>
#include <KLocale>
#include <KTextEditor/Document>
#include <KTextEditor/View>
#include <KTextEditor/Editor>
#include <KTextEditor/EditorChooser>
#include <KMessageBox>

#include "editormanager.h"
#include "kscopeconfig.h"

/**
 * Class constructor.
 * @param	pParent	The parent widget
 * @param	szName	The widget's name
 */
EditorManager::EditorManager(QWidget* pParent) :
	KParts::PartManager(pParent)
{
    m_pEditor = KTextEditor::EditorChooser::editor();
    if (!m_pEditor) {
        KMessageBox::error(pParent, i18n("A text-editor component could not be found;\n"
                    "please check your KDE installation."));
        kapp->exit(1);
    }

	applyPrefs();
}

/**
 * Class destructor.
 */
EditorManager::~EditorManager()
{
}

/**
 * Creates a new document part.
 * @return	A pointer to the new document
 */
KTextEditor::Document* EditorManager::add()
{
	KTextEditor::Document* pDoc;
	
	// Create the document
    pDoc = m_pEditor->createDocument(0);
	addPart(pDoc);

	return pDoc;
}

/**
 * Deletes a document part.
 * @param	pDoc	The document to remove
 */
void EditorManager::remove(KTextEditor::Document* pDoc)
{
	removePart(pDoc);
	delete pDoc;
}

/**
 * Applies the user preferences.
 * Determines if Kate warnings are displayed in case the currently edited
 * file is modified outside KScope.
 * NOTE: This behaviour is determined by a static function, which is why this
 * code appears here, rather then for every EditorPage object.
 */
void EditorManager::applyPrefs()
{
    // TODO
#if 0
	Kate::Document::setFileChangedDialogsActivated(
		Config().getWarnModifiedOnDisk());
#endif
}

#include "editormanager.moc"
