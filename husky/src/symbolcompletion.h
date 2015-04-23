#ifndef SYMBOLCOMPLETION_H
#define SYMBOLCOMPLETION_H

#include <qobject.h>
#include <qregexp.h>
#include <QList>

#include <KTextEditor/CodeCompletionInterface>
#include <KTextEditor/View>

#include "cscopefrontend.h"

/**
 * This class executes symbol definition queries based on symbol prefixes.
 * The results can then be displayed as symbol completion lists.
 * @author Albert Yosher
 */
class SymbolCompletion : public QObject
{
	Q_OBJECT

public:
	/**
	 * A pure-virtual class that allows a SymbolCompletion object access to
	 * text-editing objects.
	 * Classes that wish to utilise SymbolCompletion need to inplement this
	 * interface.
	 * @author Albert Yosher
	 */
	struct Interface {
		/**
	 	 * Class destructor.
	 	 * NOTE: A virtual destructor is required by GCC 4.0
		 */
		virtual ~Interface() {}

		/**
		 * Returns the word currently under the editing cursor.
		 * Symbol completion will be provided for this word only if the cursor
		 * is positioned at the end of this word.
		 * @param	pPosInWord	Set this value to the offset in the word on
		 * 						which the cursor is positioned
		 */
		virtual QString getWordUnderCursor(uint* pPosInWord) = 0;
		
		/**
		 * Returns a target object for displaying the completion list.
		 * @return	A pointer to an object implementing
		 *			KTextEditor::CodeCompletionInterface, or NULL if the
		 *			implementation does not support this interface.
		 */
		virtual QObject* getCCObject() = 0;
	};
	
    SymbolCompletion(SymbolCompletion::Interface*, QObject* pParent = 0, 
		const char* szName = 0);
    ~SymbolCompletion();

	void abort();
	
	static void initAutoCompletion(bool, uint, uint, uint);
	
public slots:
	void slotComplete();
	void slotAutoComplete();
		
private:
	/**
	 * Symbol completion entry object, used in the completion list.
	 * Implements operators required for sorting the completion list.
	 * @author Albert Yosher
	 */
	//class Entry : public KTextEditor::CompletionEntry
	class Entry
	{
	public:
		/**
		 * Determines whether a given entry is smaller than this one.
		 * @param	entry	The entry to compare with
		 * @return	true if the given entry is smaller, false otherwise
		 */
		bool operator < (const SymbolCompletion::Entry& entry) const {
			return (text < entry.text);
		}
			
		/**
		 * Determines whether a given entry is equal to this one.
		 * @param	entry	The entry to compare with
		 * @return	true if the given entry equals this one, false otherwise
		 */
		bool operator == (const SymbolCompletion::Entry& entry) const {
			return (text == entry.text);
		}
	};
	
	/**
	 * A sortable version of the value list used by CodeCompletionInterface.
	 * @author Albert Yosher
	 */
	class EntryList : public QList<Entry>
	{
	public:
		/** 
		 * Sorts completion list.
		 */
		void sort() { qHeapSort(*this); }
		 
		 /**
		  * Type casting support required for calling showCompletionBox().
		  * @return	A casted reference to this object
		  */
#if 0 // TODO
		 operator QList<KTextEditor::CompletionItem>() 
		 	{ return *(QList<KTextEditor::CompletionItem>*)this; }
#endif
	};
	
	/** Editor object for which symbol completion is provided. */
	Interface* m_pEditor;
	
	/** An object that supports KTextEditor::CodeCompletionInterface, as
		supplied by the editor. */
	QObject* m_pCCObject;
	
	/** Cscope process used to run completion queries. */
	CscopeFrontend* m_pCscope;
	
	/** The prefix used for the current query. */
	QString m_sPrefix;
	
	/** A list of possible completions for the given prefix. */
	EntryList m_elEntries;
	
	/** The maximal number of completions to accept. */
	uint m_nMaxEntries;
	
	/** Regular expression for extracting a symbol out of Cscope's text field.
		NOTE: This member is required due to a bug in Cscope that renders the
		symbol field useless. */
	QRegExp m_reSymbol;
	
	/** Auto-completion timer. */
	QTimer* m_pAutoCompTimer;
	
	/** Auto-completion flag */
	bool m_bAutoCompletion;
	
	void complete(const QString&, int nMaxEntries = 1000);
	void filterEntries();
	void makeErrMsg(const QString&);
	
	/** true if auto-completion is enabled, false otherwise. */
	static bool s_bACEnabled;
	
	/** The minimum number of characters a symbol must have for
		auto-completion. */
	static uint s_nACMinChars;
	
	/** The interval between the time slotAutoComplete() is called and the
		time the completion process begins (in milliseconds). */
	static uint s_nACDelay;
	
	/** The maximal number of entries for auto-completion. */
	static uint s_nACMaxEntries;
	
private slots:
	void slotAutoCompleteTimeout();
	void slotAddEntry(FrontendToken*);
	void slotQueryFinished(uint);
	void slotFilterInsert(KTextEditor::CompletionItem*, QString*);
};

#endif