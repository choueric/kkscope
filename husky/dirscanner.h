#ifndef DIRSCANNER_H
#define DIRSCANNER_H

#include <qobject.h>
#include <qevent.h>
#include <qthread.h>
#include <qdir.h>
#include <qstringlist.h>
#include <QHash>
#include <QTreeWidgetItem>
#include <QEvent>

class DirScanner;

/**
 * Defines a new event that can be used to pass progress information from the
 * dir scanning thread to the main application thread.
 * @author Elad Lahav
 */
class DirScanEvent : public QEvent
{
public:
	/** The event's unique ID. */
	enum { EventId = 6924 };
	
	DirScanEvent(int, bool);

	/** The number of files already scanned. */
	int m_nFiles;
	
	/** True if the dir scanning thread has finished, false otherwise. */
	bool m_bFinished;
};

/**
 * A set of unique strings.
 * Qt3 does not have a set class, so this is a simple implementation based on
 * a QHash of dummy int pointers.
 * @author	Elad Lahav
 */
class StringSet : public QHash<QString, int>
{
public:
	StringSet() : QHash<QString, int>() {}
	
	void insert(const QString& sItem) {
		static int nDummy = 0;
		QHash<QString, int>::insert(sItem, nDummy);
	}
	
	bool exists(const QString& sItem) {
		return find(sItem) != end();
	}
};

/**
 * Scans a directory for files matching a given pattern, using a separate thread.
 * @author Elad Lahav
 */
class DirScanner : public QThread
{
public: 
	DirScanner(QObject*, QHash<QString, QTreeWidgetItem>*);
	~DirScanner();

	void start(const QString&, const QString&, bool);
	
	/**
	 * @return	The list of files scanned by this thread.
	 */
	const QStringList& getFiles() { return m_slFiles; }
	
	/**
	 * Stops a scanning process, by setting the object's cancel flag.
	 */
	void cancel() { m_bCancel = true; }
	
	/**
	 * @return	true if the user has cancelled the process, false otherwise
	 */
	bool wasCancelled() { return m_bCancel; }
	
protected:
	virtual void run();

private:
	/** Pointer to an object that receives the scanner update events. */
	QObject* m_pEventReceiver;
	
	/** Currently scanned directory. */
	QDir m_dir;
	
	/**
	 * A set of already-scanned directories (prevents infinite loops in case
	 * of cyclic symbolic links in the scanned file system).
	 */
	StringSet m_setScanned;
	
	/** Pointer to a list of files indexed by the file path (used to identify
		files that should not appear in the scan results.) */
	QHash<QString, QTreeWidgetItem>* m_pDicFiles;
	
	/** Regular expression for scanning source files. */
	QString m_sNameFilter;
	
	/** The list of scanned file paths. */
	QStringList m_slFiles;
	
	/** A cancellation flag. Stops the scanning process when raised. */
	bool m_bCancel;
	
	/** true to descend to child directories, false otherwise. */
	bool m_bRecursive;
	
	int scanDir(QDir&);
};

#endif
