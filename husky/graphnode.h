#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include <QGraphicsScene>
#include <QGraphicsPolygonItem>
#include <QHash>
#include "graphedge.h"

/**
 * A canvas item that draws the name of a function insider a filled rectangle.
 * This item represents a function in the call graph.
 * @author Elad Lahav
 */
class GraphNode : public QGraphicsPolygonItem
{
public:
	GraphNode(QGraphicsScene* pCanvas, const QString&, bool bMultiCall = false);
	~GraphNode();

	GraphEdge* addOutEdge(GraphNode*);
	void dfs();
	void removeOutEdges();
	void removeInEdges();
	void getFirstNeighbour(GraphNode*&, bool&);
	
	/**
	 * @param	rect	The bounding rectangle of the node
	 */
	void setRect(const QRect& rect);
	
	/**
	 * @param	font	The font to use for drawing the text
	 */
	void setFont(const QFont& font) { m_font = font; }
	
	/**
	 * @return	The name of the function
	 */
	const QString& getFunc() const { return m_sFunc; }
	
	/**
	 * @return	true for a multiple-call node, false otherwise
	 */
	bool isMultiCall() { return m_bMultiCall; }
	
	/**
	 * @return	The set of outgoing edges
	 */
	QHash<QString, GraphEdge *>& getOutEdges() { return m_dictOutEdges; }
	
	/**
	 * @return	true if this node was already visited during the current DFS,
	 *			false otherwise
	 */
	bool dfsVisited() { return m_bDfsFlag; }
	
	/**
	 * Clears the 'DFS-visited' flag, in preparation for the next DFS.
	 */
	void dfsReset() { m_bDfsFlag = false; }
	
	/** Identifies this class among other QCanvasItem classes. */
	static int RTTI;

	/**
	 * @return	The class identifier
	 */
	virtual int rtti() const { return RTTI; }
	
protected:
	virtual void drawShape(QPainter&);
	
private:
	/** Function name. */
	QString m_sFunc;

	/** A list of outgoing edges indexed by destination. */
	QHash<QString, GraphEdge *> m_dictOutEdges;

	/** A list of incoming edges indexed by destination. */
	QHash<QString, GraphEdge *> m_dictInEdges;

	/** The bounding rectangle for the node. */
	QRect m_rect;

	/** The font to use for drawing the text. */
	QFont m_font;
	
	/** true for a multiple-call node, false otherwise. */
	bool m_bMultiCall;
	
	/** Determines whether this node was visited during a depth-first 
		search. */
	bool m_bDfsFlag;
};

#endif
