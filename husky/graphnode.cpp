#include <QPolygonF>
#include <qpainter.h>
#include <qfontmetrics.h>
#include "graphnode.h"

int GraphNode::RTTI = 1001;

/**
 * Class constructor.
 * @param	pCanvas		The owner canvas
 * @param	sFunc		The node's function
 * @param	bMultiCall	Whether this node represents multiple calls
 */
GraphNode::GraphNode(QGraphicsScene *pCanvas, const QString& sFunc, bool bMultiCall) : 
	QGraphicsPolygonItem(), // TODO
	m_sFunc(sFunc),
	m_bMultiCall(bMultiCall),
	m_bDfsFlag(false)
{
    pCanvas->addItem(this);
	// Every node deletes its out-edges only
	// m_dictOutEdges.setAutoDelete(true);   // TODO
}

/**
 * Class destructor.
 */
GraphNode::~GraphNode()
{
}

/**
 * Finds an edge leaving this node and reaching the given node.
 * If such an edge does not exist, a new one is created.
 * @param	pTail	The destination node
 * @return	The edge that ends at the given node
 */
GraphEdge* GraphNode::addOutEdge(GraphNode* pTail)
{
	GraphEdge* pEdge = NULL;
	
	// Look for the edge
	if ((pEdge = m_dictOutEdges.value(pTail->getFunc())) == NULL) {
		// Create a new edge
		pEdge = new GraphEdge(scene(), this, pTail);
		m_dictOutEdges.insert(pTail->getFunc(), pEdge);
        delete pTail->m_dictInEdges.take(m_sFunc);
		pTail->m_dictInEdges.insert(m_sFunc, pEdge);
	}
	
	// Return the new/constructed edge
	return pEdge;
}

/**
 * Performs a weak depth-first-search on the graph.
 * The search continues along all edges, both incoming and outgoing.
 */
void GraphNode::dfs()
{
	// Stop if this node is already marked
	if (m_bDfsFlag)
		return;
		
	// Mark the node as visited
	m_bDfsFlag = true;
		
	// Continue along outgoing edges
    QHashIterator<QString, GraphEdge *> itrOut(m_dictOutEdges);
    while (itrOut.hasNext()) {
        itrOut.next();
        itrOut.value()->getTail()->dfs();
    }
		
	// Continue along incoming edges
    QHashIterator<QString, GraphEdge *> itrIn(m_dictInEdges);
    while (itrIn.hasNext()) {
        itrIn.next();
        itrIn.value()->getHead()->dfs();
    }
}
	
/**
 * Deletes all outgoing edges.
 * Uses the auto-delete property of the dictionary.
 */
void GraphNode::removeOutEdges()
{
	m_dictOutEdges.clear();
}

/**
 * Deletes all incoming edges.
 * To avoid double deletions, the function lets the head node of the edge remove
 * it.
 */
void GraphNode::removeInEdges()
{
	// Delete edges through their head nodes
    QHashIterator<QString, GraphEdge *> itr(m_dictInEdges);
    while (itr.hasNext()) {
        itr.next();
        itr.value()->getHead()->m_dictOutEdges.remove(m_sFunc);
    }
	
	// remove edges from the local dictionary (will not delete them)
	m_dictInEdges.clear();
}

/**
 * Returns the first found node connected to this one.
 * This function is used with multi-call nodes for retrieving the parent node.
 * @param	pNode
 * @param	bCalled
 */
void GraphNode::getFirstNeighbour(GraphNode*& pNode, bool& bCalled)
{
    QHashIterator<QString, GraphEdge *> itrIn(m_dictInEdges);
    QHashIterator<QString, GraphEdge *> itrOut(m_dictOutEdges);
	
    if (itrIn.hasNext()) {
        itrIn.next();
        pNode = itrIn.value()->getHead();
		bCalled = false;
    } else if (itrOut.hasNext()) {
        itrOut.next();
        pNode = itrOut.value()->getTail();
		bCalled = true;
	} else {
		pNode = NULL;
	}
}

/**
 * Modifies the bounding rectangle of the node.
 * @param	rect	The new coordinates to set
 */
void GraphNode::setRect(const QRect& rect)
{
	QPolygonF arr(4);
	
	m_rect = rect;
	
	arr << QPointF(m_rect.topLeft());
	arr << QPointF(m_rect.topRight());
	arr << QPointF(m_rect.bottomRight());
	arr << QPointF(m_rect.bottomLeft());
	setPolygon(arr);
}

/**
 * Draws the node.
 * @param	painter	Used for drawing the item on the canvas view
 */
void GraphNode::drawShape(QPainter& painter)
{
	const QPen& pen = painter.pen();
	const QFont& font = painter.font();
	
	// Draw the rectangle
	painter.setPen(QPen(Qt::black));
	painter.drawRect(m_rect);
	
	// Draw the text
	painter.setPen(pen);
	painter.setFont(m_font);
	if (m_bMultiCall)
		painter.drawText(m_rect, Qt::AlignCenter, "...");
	else
		painter.drawText(m_rect, Qt::AlignCenter, m_sFunc);
	
	painter.setFont(font);
}
