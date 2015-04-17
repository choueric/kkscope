#include <kstandarddirs.h>
#include "configfrontend.h"
#include <QProcessEnvironment>

/**
 * Class constructor.
 * @param	bAutoDelete	True to destroy the object when the process ends,
 *						false otherwise
 */
ConfigFrontend::ConfigFrontend(bool bAutoDelete) : 
	Frontend(1, bAutoDelete)
{
}

/**
 * Class destructor.
 */
ConfigFrontend::~ConfigFrontend()
{
}

	
bool ConfigFrontend::run(const QString& sName, const QStringList& slArgs,
		const QString& sWorkDir, bool bBlock)
{
	if (!Frontend::run(sName, slArgs, sWorkDir, bBlock))
		return false;
		
	emit test(CscopePath);
	return true;
}

/**
 * Executes the script using the "sh" shell.
 * @param	sCscopePath		If given, overrides the automatic check for Cscope's
 *							path
 * @param	sCtagsPath		If given, overrides the automatic check for Ctags'
 *							path
 * @param	sDotPath		If given, overrides the automatic check for Dot's
 *							path
 * @param	bCscopeOptsOnly	Only verify cscope's path and options
 * @return	true if successful, false otherwise
 */
bool ConfigFrontend::run(const QString& sCscopePath, 
	const QString& sCtagsPath, const QString& sDotPath,
	bool bCscopeOptsOnly)
{
	QStringList slArgs;
	KStandardDirs sd;
	QString sScript;
	
	// Execute using the user's shell
	// setUseShell(true);
	
	// Find the configuration script
    // TODO: husky/script/kscope_config
	sScript = sd.findResource("data", "kscope/kscope_config");
	if (sScript.isEmpty())
		return false;
		
	// Set command line arguments
	slArgs.append("sh");
	slArgs.append(sScript);
	
	if (bCscopeOptsOnly)
		slArgs.append("-co");
		
	// Initialise environment
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
	env.insert("CSCOPE_PATH", sCscopePath);
	env.insert("CTAGS_PATH", sCtagsPath);
	env.insert("DOT_PATH", sDotPath);
    setProcessEnvironment(env);
	
	// Parser initialisation
	m_delim = Newline;
	m_nNextResult = CscopePath;

    const QString cmd = slArgs.join(" ");
    setShellCommand(cmd);
	
    return run("sh", slArgs);
}

/**
 * Handles tokens generated by the script.
 * Each token represents a line in the script's output, and is the result of
 * a different test.
 * @param	sToken	The generated token
 */
Frontend::ParseResult ConfigFrontend::parseStdout(QString& sToken, 
	ParserDelim)
{
	uint nResult;
	
	// Store the type of test for which the given token in the result
	nResult = m_nNextResult;
	
	// Determine the next test
	switch (m_nNextResult) {
	case CscopePath:
		if (sToken == "ERROR")
			m_nNextResult = CtagsPath;
		else
			m_nNextResult = CscopeVersion;
		break;
		
	case CscopeVersion:
		if (sToken == "ERROR")
			m_nNextResult = CtagsPath;
		else
			m_nNextResult = CscopeVerbose;
		break;
		
	case CscopeVerbose:
		m_nNextResult = CscopeSlowPath;
		break;
		
	case CscopeSlowPath:
		m_nNextResult = CtagsPath;
		break;
		
	case CtagsPath:
		if (sToken == "ERROR")
			m_nNextResult = END;
		else
			m_nNextResult = CtagsExub;
		break;
	
	case CtagsExub:
		if (sToken == "ERROR")
			m_nNextResult = END;
		else
			m_nNextResult = DotPath;
		break;
		
	case DotPath:
		if (sToken == "ERROR")
			m_nNextResult = END;
		else
			m_nNextResult = DotPlain;
		break;
	
	case DotPlain:
		m_nNextResult = END;
		break;
		
	case END:
		return DiscardToken;
	}
	
	// Publish the result and the type of the next test
	emit result(nResult, sToken);
	emit test(m_nNextResult);
	
	return DiscardToken;
}

#include "configfrontend.moc"
