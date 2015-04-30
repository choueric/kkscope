#include "husky.h"
#include <qfileinfo.h>
#include <kmessagebox.h>
#include <klocale.h>
#include <kshell.h>
#include "ctagsfrontend.h"
#include "kscopeconfig.h"

QStringList CtagsFrontend::s_slExtraArgs;

/**
 * Class constructor.
 */
CtagsFrontend::CtagsFrontend() : Frontend(CTAGS_RECORD_SIZE)
{
}

/**
 * Class destructor.
 */
CtagsFrontend::~CtagsFrontend()
{
}

bool CtagsFrontend::run(const QString& sFileName, const QStringList& slArgs,
		const QString& sWorkDir, bool bBlock)
{
	if (!Frontend::run(sFileName, slArgs, sWorkDir, bBlock)) {
		return false;
    }
	return true;
}

/**
 * Executes a Ctags process on a source file.
 * @param	sFileName	The full path to the source file
 * @return	true if successful, false otherwise
 */
// TODO: will override Frontend::run ?
bool CtagsFrontend::run(const QString& sFileName)
{
	QString sPath;
	QStringList slArgs;

	// Make sure the executable exists
	sPath = Config().getCtagsPath();

    if (sPath == "") {
        dp("ctags path is empty");
        return false;
    }

	// Set the command line arguments
	slArgs.append(sPath);
	slArgs.append("--excmd=n");
	slArgs.append("-u"); // don't sort
	slArgs.append("-f");
	slArgs.append("-");
	
	// Per-project command-line arguments
	slArgs += s_slExtraArgs;
	
	slArgs.append(sFileName);

	// Initialize stdout parsing
    if (run("ctags", slArgs)) {
        m_state = Name;
        m_delim = Tab;
        return true;
    }
    return false;
}

/**
 * Tests that the given file path leads to an executable.
 * @param	sPath	The path to check
 * @return	true if the file in the given path exists and has executable
 *			permissions, false otherwise
 */
bool CtagsFrontend::verify(const QString& sPath)
{
	QFileInfo fi(sPath);

	if (!fi.exists() || !fi.isFile() || !fi.isExecutable() ||
		fi.fileName().indexOf("ctags", 0, Qt::CaseInsensitive) == -1) {
		KMessageBox::error(0, i18n("Ctags cannot be found in the given "
			"path"));
		return false;
	}

	return true;
}

/**
 * Turns the per-project string of additional arguments into a list of 
 * command-line arguments.
 * @param	sArgs	The per-project command string
 */
void CtagsFrontend::setExtraArgs(const QString& sArgs)
{
	s_slExtraArgs = KShell::splitArgs(sArgs);
}

/**
 * Parses the output of a Ctags process.
 * @param	sToken	The current token read (the token delimiter is determined
 *					by the current state)
 * @param	delim	The delimiter that ends this token
 * @return	A value indicating the way this token should be treated: dropped,
 *			added to the token queue, or finishes a new record
 */
Frontend::ParseResult CtagsFrontend::parseStdout(QString& sToken,
	ParserDelim delim)
{
	ParseResult result = DiscardToken;

	// Handle the token according to the current state
	switch (m_state) {
	case Name:
		if (sToken.left(6) == "ctags:") {
			m_state = Other;
			m_delim = Newline;
			break;
		}

		m_state = File;
		result = AcceptToken;
		break;

	case File:
		m_state = Line;
		result = DiscardToken;
		break;

	case Line:
		sToken = sToken.left(sToken.length() - 2);
		m_state = Type;
		m_delim = All;
		result = AcceptToken;
		break;
		
	case Type:
		if (delim == Newline) {
			m_state = Name;
			m_delim = Tab;
		}
		else {
			m_state = Other;
			m_delim = Newline;
		}
		
		result = RecordReady;
		break;

	case Other:
		m_state = Name;
		m_delim = Tab;
		result = DiscardToken;
		break;

	}

	return result;
}
