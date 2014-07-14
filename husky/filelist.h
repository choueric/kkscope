#ifndef FILELIST_H
#define FILELIST_H

#include "searchlist.h"
//#include "projectmanager.h"

/**
 * Abstract base class for classes that need the list of project files.
 * Objects of classes derived from this one are used as a parameter to
 * ProjectManager::fillList(), which reads all file entries in the project,
 * and calls addItem() for each.
 * Any class that wishes to retrieve the project's file list, should inherit
 * from this class, and implement addItem().
 */
class FileListTarget
{
public:
	/**
	 * Class constructor.
	 */
	FileListTarget() {}

	/**
	 * Class destructor.
	 */
	virtual ~FileListTarget() {}

	/**
	 * Appends a file to the list.
	 * @param	sFilePath	The full path of the file to add
	 */
	virtual void addItem(const QString& sFilePath) = 0;
};


/**
 * Implements a searchable list of files.
 * The file list is composed of a list view, and a search box, into which the
 * user can enter a file name. The name is matched against the contents of
 * the list, and matching items are selected.
 * @author Elad Lahav
 */

class FileList : public SearchList, public FileListTarget
{
	Q_OBJECT

public: 
	FileList(QWidget* pParent = 0, const char* szName = 0);
	~FileList();
	
	virtual void addItem(const QString&);
	bool findFile(const QString&);
	void clear();
	void applyPrefs();
	void setRoot(const QString&);
	virtual bool getTip(QTreeWidgetItem*, QString&);
	
signals:
	/**
	 * Emitted when a file is selected, by either double-clicking a list
	 * item, or by highlighting an item and pressing the ENTER key.
	 * @param	sPath	The full path of the selected file
	 * @param	nLine	Line number, always set to 0
	 */
	void fileRequested(const QString& sPath, uint nLine);

protected:
	virtual void processItemSelected(QTreeWidgetItem*);
	
private:
	/** A common root path for all items in the list. */
	QString m_sRoot;
};

#endif
