#ifndef GRAPHEDGE_H
#define GRAPHEDGE_H

#include <QGraphicsScene>
#include <QPolygon>

class GraphNode;

/**
 * Information used to draw arrow heads at the end of graph edges.
 */
struct ArrowInfo
{
	/** The length of the arrow. */
	double m_dLength;
	
	/** The tangent of the arrow's angle from the main line. */
	double m_dTan;
	
	/** Holds the value sqrt(1 + dTan^2). */
	double m_dSqrt;
};

/**
 * Draws a directed edge on a canvas.
 * The edge is composed of a spline, which is its body, and a polygon, which
 * is its head.
 * @author Elad Lahav
 */
class GraphEdge : public QGraphicsPolygonItem
{
public:
    GraphEdge(QGraphicsScene*, GraphNode*, GraphNode*);
    ~GraphEdge();
	
	void setCallInfo(const QString&, const QString&, const QString&);
	void setPoints(const QPolygon&, const ArrowInfo&);
	QString getTip() const;
	
	/**
	 * @return	The coordinates of the convex hull surrounding the edge
	 */
	virtual QPolygon areaPoints() const { return m_arrArea; }
	
	/**
	 * @return	The head node of the edge
	 */
	GraphNode* getHead() { return m_pHead; }
	
	/**
	 * @return	The tail node of the edge
	 */
	GraphNode* getTail() { return m_pTail; }
	
	/**
	 * @return	 The bounding rectangle of the edge's head
	 */
	QRect tipRect() const { return m_rcTip; }
		
	/**
	 * @return	The file path for this call
	 */
	const QString& getFile() const { return m_sFile; }
		
	/**
	 * @return	The line number for this call
	 */
	uint getLine() const { return m_sLine.toUInt(); }
		
	/**
	 * @return	The call's text
	 */
	const QString& getText() const { return m_sText; }
	
	/** Identifies this class among other QCanvasItem classes. */
	static int RTTI;

	/** 
	 * @return	The class identifier
	 */
	virtual int rtti() const { return RTTI; }
	
protected:
	virtual void drawShape(QPainter&);
	
private:
	/** The edge's starting point. */
	GraphNode* m_pHead;
		
	/** The edge's end point. */
	GraphNode* m_pTail;
	
	/** The points of the polygon part of the edge. */
	QPolygon m_arrPoly;
	
	/** Control points for the spline part of the edge. */
	QPolygon m_arrCurve;
	
	QPolygon m_arrArea;
	
	/** The bounding rectangle of the edge's head, used for displaying the
		edge's tool-tip. */
	QRect m_rcTip;
	
	/** The call's source file. */
	QString m_sFile;
	
	/** The call's line number. */
	QString m_sLine;
	
	/** The call's text. */
	QString m_sText;
	
	void makeArrowhead(const ArrowInfo&);
};

#endif
