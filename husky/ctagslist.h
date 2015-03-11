#ifndef CTAGSLIST_H
#define CTAGSLIST_H

#include <QTreeView>
#include <QWidget>
#include <QPixmap>
#include <QVector>
#include "searchlist.h"
#include "frontend.h"

class CtagsListItem;
//class CtagsToolTip;

/**
 * Displays a list of tags for a source file.
 * The list is embedded inside an editor page. Whenever a new document is
 * opened in that editor, or the current document is changed and saved, the
 * source file is re-scanned for tags, and the results are displayed in this
 * list.
 * @author Elad Lahav
 */

class CtagsList : public SearchList
{
   Q_OBJECT

public:
	CtagsList(QWidget* pParent = 0, const char* szName = 0);
	~CtagsList();

	void applyPrefs();
	void gotoLine(uint);
	void clear();
	
	virtual bool getTip(QTreeWidgetItem*, QString&);
	
public slots:
	void slotDataReady(FrontendToken*);
	void slotCtagsFinished(uint);
	
signals:
	/** 
	 * Emitted when the size of the list is changed (usually as the result
	 * of moving the separator between the list and the editor.)
	 */
	void resized();
	
	/**
	 * Emitted when the user selects a tag item from the list.
	 * @param	nLine	The line number associated with the selected tag
	 */
	void lineRequested(uint nLine);
	
protected:
	virtual void resizeEvent(QResizeEvent*);
	virtual void processItemSelected(QTreeWidgetItem*);
	
private:
	/** An array of pointers to the tag list items, sorted by the line
		number. */
	QVector<CtagsListItem*> m_arrLines;
	
	/** The number of items in the tag list. */
	int m_nItems;
	
	/** The last item selected by gotoLine(). */
	int m_nCurItem;
	
	/** This value is set to 'false' while the Ctags process is running. */
	bool m_bReady;
	
	/** The current line number. */
	uint m_nCurLine;
	
	/** Stores the requested line number during Ctags operation. */
	uint m_nPendLine;

private slots:
	void slotSortChanged(int);
};

#endif
