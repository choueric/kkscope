#ifndef DOTFRONTEND_H
#define DOTFRONTEND_H

#include <QPolygon>

#include "frontend.h"

class GraphWidget;

/**
 * Front-end for executing graphviz's command-line tool.
 * This tool accepts the description of a graph in the 'dot' language, and
 * outputs a set of drawing instructions for the graph.
 * @author Elad Lahav
 */
class DotFrontend : public Frontend
{
	Q_OBJECT

public:
	DotFrontend(GraphWidget*);
	~DotFrontend();

	bool run(const QString&);
	bool run(const QString&, const QStringList&,
		const QString& sWorkDir = "", bool bBlock = false);
	
	static bool verify(const QString&);
	
protected:
	virtual ParseResult parseStdout(QString&, ParserDelim);

private:
	/** The owner graph widget on which to draw. */
	GraphWidget* m_pGraph;
	
	/** State values for the parser state machine. */
	enum ParserState { Graph, GraphScale, GraphWidth, GraphHeight,
		NodeEdgeStop, NodeName, NodeCentreX, NodeCentreY, NodeWidth, NodeHeight,
		EdgeHead, EdgeTail, EdgeCurveSize, EdgeCurveX, EdgeCurveY,
		EndNodeEdge };
	
	/** The current state of the parser state machine. */
	ParserState m_state;
	
	/** The horizontal DPI value of the graph widget. */
	double m_dDpiX;
	
	/** The vertical DPI value of the graph widget. */
	double m_dDpiY;
};

#endif
