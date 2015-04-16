#ifndef KSCOPEPIXMAPS_H
#define KSCOPEPIXMAPS_H

#include <QPixmap>
#include <kiconloader.h>

// TODO: just for debug 
#define ICON_PREFIX "/home/zhs/workspace/kkscope/husky/ui/pics/"

#define GET_PIXMAP(_pix) \
	Pixmaps().getPixmap(KScopePixmaps::_pix)

/**
 * Handles all pixmaps required by KScope.
 * There are two types of pixmaps: embedded, i.e., pixmaps whose pixels are
 * given by static two-dimensional arrays, and loadable, which are retrieved
 * through the KIconLoader mechanism.
 * The application uses a single global instance of this class.
 * @author Elad Lahav
 */

class KScopePixmaps
{
public: 
	KScopePixmaps();
	~KScopePixmaps();

	/** Identifiers for embedded pixmaps. */
	enum PixName { SymFunc, SymVar, SymStruct, SymMacro, SymMember, SymEnum,
		SymEnumerator, SymTypedef, SymLabel, SymInclude, SymUnknown,
		PIX_ARRAY_SIZE };
		
	/** Identifiers for loadable pixmaps. */
	enum LoadPixName { TabUnlocked, TabLocked, TabBookmark, TabRW, TabRO, 
		TabSave, TabFileList, TabFileTree, TabList, ButtonSaveAs, ButtonZoomIn,
		ButtonZoomOut, ButtonRotate, ButtonPref, CalledTree,
		CallingTree, CallGraph };
	
	void init();
	const QPixmap& getPixmap(PixName name) const;
	QPixmap getPixmap(LoadPixName name);
	
private:
	/** An array of pointers to the embedded pixmaps. */
	QPixmap** m_pPixArray;
	
	/** An icon loader used to retrieve pixmaps through the KDE mechanism. */
	KIconLoader m_loader;
};

extern KScopePixmaps& Pixmaps();

#endif
