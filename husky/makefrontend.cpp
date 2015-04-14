#include <qregexp.h>
#include "makefrontend.h"

// TODO:
// This should probably be configurable on a per-project basis.
#define PATH_ELEM "[a-zA-Z0-9_\\.\\-]+"

#define RE_FILE_LINE \
	"((?:\\/)?(?:"PATH_ELEM"\\/)*"PATH_ELEM"):([0-9]+)(:[0-9]+)?: (.*)"
#define RE_ENTER_DIR \
	"Entering directory " \
	"\\`((\\/)?("PATH_ELEM"\\/)*"PATH_ELEM")"
#define RE_EXIT_DIR "Leaving directory"

/**
 * Class constructor.
 * @param	bAutoDelete	If true, the object is deleted when the process
 *						terminates (false by default)
 */
MakeFrontend::MakeFrontend(bool bAutoDelete) : Frontend(1, bAutoDelete)
{
	// Execute inside a shell
	// setUseShell(true); // TODO
	
	// Each token represent a complete line
	m_delim = Newline;
}

/**
 * Class destructor.
 */
MakeFrontend::~MakeFrontend()
{
}

/**
 * Executes the make command.
 * @param	sName		The name of the process (for error messages)
 * @param	slArgs		A list containing the command-line arguments
 * @param	sWorkDir	Initial build directory
 * @param	bBlock		(Optional) true to block, false otherwise
 * @return	true if the process was executed successfully, false otherwise
 */
bool MakeFrontend::run(const QString& sName, const QStringList& slArgs, 
	const QString& sWorkDir, bool bBlock)
{
	QStringList slShellArgs;
	
	// Store the current build directory
	m_slPathStack.push_back(sWorkDir);
	
	// Join the output streams, so that they can both be parsed by
	// parseStdout()
	slShellArgs = slArgs;
	slShellArgs << "2>&1";
	
	// Execute the command
	return Frontend::run(sName, slShellArgs, sWorkDir, bBlock);
}

/**
 * Parses lines of output produced by the make command.
 * @param	sToken	A single line of output
 */
Frontend::ParseResult MakeFrontend::parseStdout(QString& sToken, ParserDelim)
{
	static QRegExp reErrWarn(RE_FILE_LINE);
	static QRegExp reEntDir(RE_ENTER_DIR);
	static QRegExp reExtDir(RE_EXIT_DIR);
	QString sRep;
	int nPos;
	QString sFile, sLine, sText;
	
	if ((nPos = reErrWarn.indexIn(sToken)) >= 0) {
		// An error/warning message
		if (sToken.at(nPos) == '/') {
			sFile = reErrWarn.capturedTexts()[1];
		}
		else {
			sFile = m_slPathStack.last() + "/" +
				reErrWarn.capturedTexts()[1];
		}
		
		sLine = reErrWarn.capturedTexts()[2];
		sText = reErrWarn.capturedTexts()[4];
		emit error(sFile, sLine, sText);
		
		sRep = QString("<a href=\"") + sFile + "&\\2\">\\1:\\2</a>\\3: \\4";
		sToken.replace(reErrWarn, sRep);
	}
	else if ((nPos = reEntDir.indexIn(sToken)) >= 0) {
		// Recursing into a directory
		m_slPathStack.push_back(reEntDir.capturedTexts()[1]);
		sToken = QString("<b>Entering directory</b> ") +
			m_slPathStack.last();
	}
	else if ((nPos = reExtDir.indexIn(sToken)) >= 0) {
		// Leaving a directory
		sToken = QString("<b>Leaving directory</b> ") +
			m_slPathStack.last();
		m_slPathStack.pop_back();
	}

	return RecordReady;
}

#include "makefrontend.moc"
