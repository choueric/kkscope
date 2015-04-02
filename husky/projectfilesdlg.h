#ifndef PROJECTFILESDLG_H
#define PROJECTFILESDLG_H

#include <QWidget>
#include <QHash>
#include <QEvent>

#include "project.h"
#include "ui_projectfileslayout.h"

class DirScanner;
class ScanProgressDlg;

/**
 * A dialog to manipulate the project's files.
 * The dialog allows the user to add source files to the current project, or
 * remove files from it. The main widget of the dialog is a list view, that
 * displays all files currently in the project. When files are added or
 * removed, this list view is updated. The project, however, is only modified
 * if the user closes the dialog using the "OK" button.
 * Since searches through a list view are very slow, the class also maintains
 * a QDict object, that connects file names with their respective list items.
 * This dictionary is used to ensure duplicated items are not added to the
 * list.
 * @author Elad Lahav
 */

class ProjectFilesDlg : public QDialog, public Ui_ProjectFilesLayout, public FileListTarget,
	public FileListSource
{
   Q_OBJECT

public: 
	ProjectFilesDlg(Project*, QWidget* pParent = 0,	const char* szName = 0);
	~ProjectFilesDlg();

	virtual void addItem(const QString&);
	virtual bool firstItem(QString&);
	virtual bool nextItem(QString&);

protected:
	virtual void customEvent(QEvent*);

private:
	/** The project to manipulate. */
	Project* m_pProj;

	/** Holds all file paths in a quickly searchable format (for duplicate
		entries lookup). */
	QHash<QString, QTreeWidgetItem> m_dicFiles;
	
	/** A thread object to a-synchronously scan directories for source files
		to add to the project. */
	DirScanner* m_pScanner;

	/** Displays the progress of a directory scan operation. */
	ScanProgressDlg* m_pScanDlg;

	/** A file list item that serves as an iterator. */
	QTreeWidgetItem* m_pItrItem;

	/** The last item added. */
	QTreeWidgetItem* m_pLastItem;
	
	void removeItem(QTreeWidgetItem*);
	
private slots:
	void slotAddFiles();
	void slotAddDir();
	void slotAddTree();
	void slotRemSel();
	void slotRemDir();
	void slotRemTree();
	void slotFilter();
	void slotShowAll();
	void slotCancelDirScan();
};

#endif
