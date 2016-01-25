#include <QDebug>
#include <QTreeWidget>
#include <qpainter.h>
#include <kfontdialog.h>
#include <klocale.h>
#include "preffont.h"
#include "kscopeconfig.h"

/**
 * A list view item that shows the name of a GUI element and the font
 * associated with it.
 * The font is presented in the form of a sample text drawn using this font.
 * @author	Elad Lahav
 */
class FontListItem : public QTreeWidgetItem
{
public:
	/**
	 * Class constructor.
	 * @param	pList	The owner list view
	 * @param	fe		The GUI element shown by this item
	 */
	FontListItem(QTreeWidget* pList, KScopeConfig::FontElement fe) : 
		QTreeWidgetItem(pList),
		m_fe(fe) {
        setText(0, Config().getFontName(fe));
        setText(1, "Sample");
		setFont(Config().getFont(fe));
	}
	
	/**
	 * @return	The GUI element shown by this item
	 */
	KScopeConfig::FontElement getElement() { return m_fe; }
	
	/**
	 * Changes the font associated with this item.
	 */
	void setFont(QFont font) {
		m_font = font;
		QTreeWidgetItem::setFont(1, font);
	}
	
	/**
	 * @return	The font associated with this item
	 */
	QFont getFont() { return m_font; }
	
private:
	/** The GUI element shown by this item. */
	KScopeConfig::FontElement m_fe;
	
	/** The font associated with this item. */
	QFont m_font;
};

/**
 * Class constructor.
 * @param	pParent	The parent widget
 * @param	szName	The widget's name
 */
PrefFont::PrefFont(QWidget* pParent):
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
PrefFont::~PrefFont()
{
}

/**
 * Reads the current settings from the configuration object, and applies them
 * the the page's widget.
 */
void PrefFont::load()
{
	uint i;
	
	// Create a list item for every GUI element
	for (i = 0; i <= KScopeConfig::LAST_FONT; i++)
		new FontListItem(m_pList, (KScopeConfig::FontElement)i);
}

/**
 * Commits settings changes to the configuration object.
 */
void PrefFont::apply()
{
	FontListItem* pItem;
	
	// Create a list item for every GUI element
    QTreeWidgetItem *p;
    QTreeWidgetItemIterator it(m_pList);
    for (; *it; ++it) {
        p = *it;
        pItem = (FontListItem *)p;
		Config().setFont(pItem->getElement(), pItem->getFont());
		qDebug() << "set font" << pItem->getFont();
    }
}

/**
 * Displays a font selection dialogue when an item is selected.
 * If the user chooses a new font, it is set to the selected item.
 * This slot is connected to both the doubleClicked() and the returnPressed()
 * signals of the list view.
 * @param	pItem	The selected item
 */
void PrefFont::slotItemSelected(QTreeWidgetItem* pItem)
{
	FontListItem* pFontItem;
	QFont font;
	
	pFontItem = (FontListItem*)pItem;
	font = pFontItem->getFont();
	if (KFontDialog::getFont(font) == QDialog::Accepted) {
		pFontItem->setFont(font);
		qDebug() << "set font" << font;
		emit modified();
	}
}
