#ifndef MAKEFRONTEND_H
#define MAKEFRONTEND_H

#include "frontend.h"

/**
 * A shell-process front-end intended for running make-like tasks.
 * Records are single-line tokens delimited by newline characters. The parser
 * replaces references to source lines (e.g., filename:123) with hypertext
 * links for use in a browser.
 * @author Elad Lahav
 */
class MakeFrontend : public Frontend
{
	Q_OBJECT
	
public:
	MakeFrontend(bool bAutoDelete = false);
	~MakeFrontend();

	virtual bool run(const QString&, const QStringList&, 
		const QString&, bool bBlock = false);
	virtual ParseResult parseStdout(QString&, ParserDelim);
	
signals:
	void error(const QString& sFile, const QString& sLine,
		const QString& sText);
	
private:
	/** A stack of paths used to track the current build directory. */
	QStringList m_slPathStack;
};

#endif
