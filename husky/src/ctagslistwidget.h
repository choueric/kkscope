#ifndef _CTAGSLISTWIDGET_H
#define _CTAGSLISTWIDGET_H

#include <QTreeView>
#include <QWidget>
#include <QPixmap>
#include <QVector>
#include "searchlistview.h"
#include "stringlistmodel.h"
#include "frontend.h"

/**
 * Displays a list of tags for a source file with QTreeWidget.
 * The list is embedded inside an editor page. Whenever a new document is
 * opened in that editor, or the current document is changed and saved, the
 * source file is re-scanned for tags, and the results are displayed in this
 * list.
 */
class CtagsListWidget : public SearchListView
{
   Q_OBJECT

public:
	CtagsListWidget(QWidget* pParent = 0);
	~CtagsListWidget();

	void applyPrefs();
	void gotoLine(uint);
	void clear();
    void focusOnEdit();
	
    virtual bool getTip(QModelIndex &index, QString& sTip);
	
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
    virtual void processItemSelected(const QModelIndex &);
	
private:
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

    StringListModel *m_pModel;

private slots:
	void slotSortChanged(int);
};

#endif
