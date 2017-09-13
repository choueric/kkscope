#ifndef CONFIGFRONTEND_H
#define CONFIGFRONTEND_H

#include "frontend.h"

/**
 * Frontend to the kscope_config shell script.
 * The script executes a set of tests and outputs their results.
 * @author Elad Lahav
 */
class ConfigFrontend : public Frontend
{
	Q_OBJECT

public:
	ConfigFrontend(bool bAutoDelete = false);
	~ConfigFrontend();
	
	bool run(const QString&, const QString&,
		bool bCscopeOptsOnly = false);
	bool run(const QString&, const QStringList&,
		const QString& sWorkDir = "", bool bBlock = false);
	
	/**
	 * The types of tests executed by the script.
	 */
	enum { CscopePath, CscopeVersion, CscopeVerbose, CscopeSlowPath,
		CtagsPath, CtagsExub, END };
	
signals:
	/**
	 * Indicates that the script is now running a given test.
	 * @param	nType	The type of test being executed
	 */
	void test(uint nType);
	
	/**
	 * Called after a test has produced a result.
	 * @param	nType	The type of test executed
	 * @param	sResult	The obtained result
	 */
	void result(uint nType, const QString& sResult);
	
protected:
	virtual ParseResult parseStdout(QString&, ParserDelim);
	
private:
	/** The type of test whose result is expected next. */
	uint m_nNextResult;
};

#endif
