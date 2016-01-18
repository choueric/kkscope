#ifndef FILELISTWIDGET_H
#define FILELISTWIDGET_H

#include "searchlistview.h"
#include "stringlistmodel.h"
#include "projectmanager.h"

class FileListWidget : public SearchListView, public FileListTarget
{
	Q_OBJECT

public: 
	FileListWidget(QWidget* pParent = 0);
	~FileListWidget();
	
	virtual void addItem(const QString&);
	bool findFile(const QString&);
	void clear();
	void applyPrefs();
	void setRoot(const QString&);
    virtual bool getTip(QModelIndex &index, QString& sTip);
	
signals:
	/**
	 * Emitted when a file is selected, by either double-clicking a list
	 * item, or by highlighting an item and pressing the ENTER key.
	 * @param	sPath	The full path of the selected file
	 * @param	nLine	Line number, always set to 0
	 */
	void fileRequested(const QString& sPath, uint nLine);

protected:
    virtual void processItemSelected(const QModelIndex &);
	
private:
	/** A common root path for all items in the list. */
	QString m_sRoot;
    StringListModel *m_pModel;
};

#endif
