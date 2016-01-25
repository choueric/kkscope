#include <QWidget>
#include <QTreeWidgetItem>
#include <qpainter.h>
#include <kcolordialog.h>

#include <stdio.h>
#include "prefcolor.h"
#include "kscopeconfig.h"

/**
 * A list view item that shows the name of a GUI element and the colour
 * associated with it.
 * The colour is presented in the form of a rectangle filled with that
 * colour.
 * @author	Elad Lahav
 */
class ColorListItem : public QTreeWidgetItem
{
public:
	/**
	 * Class constructor.
	 * @param	pList	The owner list view
	 * @param	ce		The GUI element shown by this item
	 */
	ColorListItem(QTreeWidget* pList, KScopeConfig::ColorElement ce) : 
		QTreeWidgetItem(pList),
        m_ce(ce) {
            setText(0, Config().getColorName(ce));
            setText(1, "");
            setColor(Config().getColor(ce));
	}
	
	/**
	 * @return	The GUI element shown by this item
	 */
	KScopeConfig::ColorElement getElement() { return m_ce; }
	
	/**
	 * Changes the colour associated with this item.
	 * The function assigns a pixmap to the item which shows a rectangle
	 * filled with the requested colour.
	 * The colour set by this function is returned by getColor().
	 * @param	clr		The colour to set
	 */
	void setColor(QColor clr) {
        QBrush b(clr);

		// Remember the colour
		m_clr = clr;
		
		// Set the pixmap to the item
        setBackground(1, b);
        setForeground(1, b);
	}
	
	/**
	 * @return	The colour associated with this item
	 */
	QColor getColor() { return m_clr; }
	
private:
	/** The GUI element shown by this item. */
	KScopeConfig::ColorElement m_ce;
	
	/** The colour associated with this item. */
	QColor m_clr;
};

/**
 * Class constructor.
 * @param	pParent	The parent widget
 * @param	szName	The widget's name
 */
PrefColor::PrefColor(QWidget* pParent):
    QWidget(pParent)
{
    setupUi(this);
	
	// Set initial values
	load();

	connect(m_pList, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, 
		SLOT(slotItemSelected(QTreeWidgetItem*)));
}

/**
 * Class destructor.
 */
PrefColor::~PrefColor()
{
}

/**
 * Reads the current settings from the configuration object, and applies them
 * the the page's widget.
 */
void PrefColor::load()
{
	uint i;
	
	// Create a list item for every GUI element
	for (i = 0; i <= KScopeConfig::LAST_COLOR; i++) {
		new ColorListItem(m_pList, (KScopeConfig::ColorElement)i);
    }
    m_pList->resizeColumnToContents(0);
}

/**
 * Commits settings changes to the configuration object.
 */
void PrefColor::apply()
{
	ColorListItem* pItem;

	// Create a list item for every GUI element
    QTreeWidgetItem *p;
    QTreeWidgetItemIterator it(m_pList);
    for (; *it; ++it) {
        p = *it;
        pItem = (ColorListItem *)p;
		Config().setColor(pItem->getElement(), pItem->getColor());
    }
    m_pList->resizeColumnToContents(0);
}

/**
 * Displays a colour selection dialogue when an item is selected.
 * If the user chooses a new colour, it is set to the selected item.
 * This slot is connected to both the doubleClicked() and the returnPressed()
 * signals of the list view.
 * @param	pItem	The selected item
 */
void PrefColor::slotItemSelected(QTreeWidgetItem* pItem)
{
	ColorListItem* pClrItem;
	QColor clr;

	pClrItem = (ColorListItem*)pItem;
	if (KColorDialog::getColor(clr, pClrItem->getColor()) == 
		QDialog::Accepted) {
		pClrItem->setColor(clr);
		emit modified();
	}
}
