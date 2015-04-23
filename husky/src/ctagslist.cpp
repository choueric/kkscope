#include <QTreeWidget>
#include <iostream>

#include <QHeaderView>
#include <KLocale>
#include "ctagslist.h"
#include "kscopeconfig.h"
#include "kscopepixmaps.h"

#define HEADER_COUNT 3
#define HEADER_NAME 0
#define HEADER_LINE 1
#define HEADER_TYPE 2

/**
 * Defines a special list item for the tag list.
 * This special definition allows the tag list to be sorted according to
 * symbol line numbers. By default, all items are treated as text, hence the
 * comparison of line numbers such as "123" and "24" sets "24" to be the
 * larger item. By overriding the comparison function, this class allows for
 * correct sorting.
 * @author Elad Lahav
 */
class CtagsListItem : public QTreeWidgetItem
{
public:
	/**
	 * Class constructor.
	 * @param	pParent	The owning list view widget
	 * @param	sName	The name of the tag
	 * @param	sLine	The line in which the tag is defined
	 * @param	sType	The type of the tag
	 */
	CtagsListItem(QTreeWidget* pParent, QString sName, QString sLine, QString sType) :
        QTreeWidgetItem(pParent), m_nPendLine (sLine.toUInt()) {
        setText(HEADER_NAME, sName);  // Symbol Name
        setText(HEADER_LINE, sLine);  // Line Number
        setText(HEADER_TYPE, sType);  // Symbol Type
    }

	/**
	 * Compares two tag list items, and determines their order.
	 * If comparison is based on a text-column, the default behaviour is
	 * used. Otherwise, the text is converted to unsigned integers, and then
	 * compared as numbers.
	 * @param	pItem	The item to compare against the local object
	 * @param	nCol	The column index by which to compare
	 * @param	bAscend	true if sorting in ascending order, false otherwise
	 * @return	0 if the items are equal, 1 if the local item is greater, -1
	 * 			if the local item is lesser
	 */
	virtual int compare(QTreeWidgetItem* pItem, int nCol, bool bAscend) const {
		if (nCol == HEADER_NAME) {
			uint nLineCur, nLineOther;
			int nResult;

			// Get the line numbers of each item
			nLineCur = text(HEADER_NAME).toUInt();
			nLineOther = pItem->text(HEADER_NAME).toUInt();

			// Compare the line numbers
			nResult = nLineCur - nLineOther;
			if (nResult == 0)
				return 0; // Items are equal
			else if (nResult > 0)
				return 1; // The first item is greater
			else
				return -1; // The second item is greater
		}

        QString self = text(nCol);
        QString other = pItem->text(nCol);
        return bAscend ? QString::compare(self, other): QString::compare(other, self);
	}

	/**
	 * @return	The line number associated with this item
	 */	
	inline uint getLine() { return m_nPendLine; }
	
private:
	/** The numeric value of the line number column of this item. */
	uint m_nPendLine;		
};

/**
 * Class constructor.
 * @param	pParent	The parent widget
 * @param	szName	The widget's name
 */
CtagsList::CtagsList(QWidget* pParent) :
	SearchList(0, pParent),
	m_arrLines(16),
	m_nItems(0),
	m_nCurItem(0),
	m_bReady(false),
	m_nCurLine(0),
	m_nPendLine(0)
{
	connect(m_pList->header(), SIGNAL(clicked(int)), this,
		SLOT(slotSortChanged(int)));
	
	// Determine the default sorting order
	switch (Config().getCtagSortOrder()) {
	case KScopeConfig::NameAsc:
		m_pList->sortItems(HEADER_NAME, Qt::AscendingOrder);
		break;
		
	case KScopeConfig::NameDes:
		m_pList->sortItems(HEADER_NAME, Qt::DescendingOrder);
		break;
		
	case KScopeConfig::LineAsc:
		m_pList->sortItems(HEADER_LINE, Qt::AscendingOrder);
		break;
		
	case KScopeConfig::LineDes:
		m_pList->sortItems(HEADER_LINE, Qt::DescendingOrder);
		break;
		
	case KScopeConfig::TypeAsc:
		m_pList->sortItems(HEADER_TYPE, Qt::AscendingOrder);
		break;
		
	case KScopeConfig::TypeDes:
		m_pList->sortItems(HEADER_TYPE, Qt::DescendingOrder);
		break;
	}
				
	// Add the list columns
    m_pList->setColumnCount(HEADER_COUNT);
    QStringList strList;
    strList << i18n("Name") << i18n("Line") << i18n("Type");
    m_pList->setHeaderLabels(strList);
    m_pList->setRootIsDecorated(false);
    m_pList->header()->setResizeMode(QHeaderView::ResizeToContents);
    m_pList->setSortingEnabled(true);

    // TODO: to complicated to do so, so don't set it right now.
	//m_pList->setColumnAlignment(1, Qt::AlignRight);

	// Set colours and font
	applyPrefs();
}

/**
 * Class destructor.
 */
CtagsList::~CtagsList()
{
}

/**
 * Adds a Ctags output entry to the list.
 * This slot is connected to the dataReady() signal of a CtagsFrontend object.
 * @param	pToken	The first token in the entry
 */
void CtagsList::slotDataReady(FrontendToken* pToken)
{
	QString sName, sType, sLine;
	CtagsListItem* pItem;
	KScopePixmaps::PixName pix;

	// Get the name of the symbol
	sName = pToken->getData();
	pToken = pToken->getNext();

	// Get the line number
	sLine = pToken->getData();
	pToken = pToken->getNext();

	// Get the type of the symbol
	sType = pToken->getData();
	pToken = pToken->getNext();

	// Set the appropriate pixmap
	//switch (sType[0].latin1()) {
	switch (sType.toAscii()[0]) {
	case 'f':
		sType = i18n("Function");
		pix = KScopePixmaps::SymFunc;
		break;
		
	case 'v':
		sType = i18n("Variable");
		pix = KScopePixmaps::SymVar;
		break;
	
	case 's':
		sType = i18n("Struct");
		pix = KScopePixmaps::SymStruct;
		break;
	
	case 'd':
		sType = i18n("Macro");
		pix = KScopePixmaps::SymMacro;
		break;
		
	case 'm':
		sType = i18n("Member");
		pix = KScopePixmaps::SymMember;
		break;
		
	case 'g':
		sType = i18n("Enum");
		pix = KScopePixmaps::SymEnum;
		break;
		
	case 'e':
		sType = i18n("Enumerator");
		pix = KScopePixmaps::SymEnumerator;
		break;
		
	case 't':
		sType = i18n("Typedef");
		pix = KScopePixmaps::SymTypedef;
		break;
		
	case 'l':
		sType = i18n("Label");
		pix = KScopePixmaps::SymLabel;
		break;

	case 'i':
		sType = i18n("Include");
		pix = KScopePixmaps::SymInclude;
		break;

    case 'c':
        sType = i18n("Class");
        pix = KScopePixmaps::SymClass;
        break;
		
	default:
		sType = "Unknown";
		pix = KScopePixmaps::SymUnknown;
	}

	// Add a new item to the list
	pItem = new CtagsListItem(m_pList, sName, sLine, sType);

    QIcon icon(Pixmaps().getPixmap(pix));
	pItem->setIcon(HEADER_NAME, icon);
	m_nItems++;
	
	// Resize the line array, if required
	if (m_arrLines.size() < m_nItems)
		m_arrLines.resize(m_nItems);
	
	// Add the new item to the line array
	m_arrLines[m_nItems - 1] = pItem;
}

/**
 * Handles the "resize" event, which occurs when the size of the widget
 * changes.
 * @param	pEvent	The event data
 */
void CtagsList::resizeEvent(QResizeEvent* pEvent)
{
	SearchList::resizeEvent(pEvent);
	emit resized();
}

/**
 * Emits the lineRequested() signal when a list item is selected.
 * This function is called if either an item is double-clicked, or an item is
 * highlighted and the ENTER key is pressed.
 * @param	pItem	The selected list item
 */
void CtagsList::processItemSelected(QTreeWidgetItem* pItem)
{
	QString sLine;

	sLine = pItem->text(HEADER_LINE);
	m_pEdit->setText(pItem->text(HEADER_NAME));
	emit lineRequested(sLine.toUInt());
}

/**
 * Constructs a tool-tip for the given item.
 * @param	pItem	The item for which a tip is required
 * @param	sTip	The constructed tip string (on return)
 * @return	Always true
 */
bool CtagsList::getTip(QTreeWidgetItem* pItem, QString& sTip)
{
	sTip = QString("Type: <b>%1</b><br>Name: <b>%2</b><br>Line: <b>%3</b>").
		arg(pItem->text(HEADER_TYPE)).arg(pItem->text(HEADER_NAME)).arg(pItem->text(HEADER_LINE));
	return true;
}

/**
 * Sets the list's colours and font, according the user's preferences.
 */
void CtagsList::applyPrefs()
{
	// Apply colour settings
    // see QueryPageBase::applyPrefs()
#if 0 // TODO
	m_pList->setPaletteBackgroundColor(Config().getColor(
		KScopeConfig::TagListBack));
	m_pList->setPaletteForegroundColor(Config().getColor(
		KScopeConfig::TagListFore));
	m_pList->setFont(Config().getFont(KScopeConfig::TagList));
#endif
}

/**
 * Selects the symbol that dominates the given line in the source file.
 * @param	nLine	The requested line
 */
void CtagsList::gotoLine(uint nLine)
{
	CtagsListItem* pItem;
	int nFrom, nTo, nItem, nDiff;
	
	// Wait until Ctags finishes
	if (!m_bReady) {
		m_nPendLine = nLine;
		return;
	}		
	
	// Do nothing if no tags are available
	if (m_nItems == 0)
		return;
	
	// Calculate the difference from the current line
	nDiff = (int)(nLine - m_nCurLine);
	m_nCurLine = nLine;
		
	// In most cases, all the user does is move to the next or prevuious lines
	// Handle these simple cases first
	if (nDiff == 1) {
		if ((m_nCurItem < m_nItems - 1) && 
			(m_arrLines[m_nCurItem + 1]->getLine() == nLine)) {
			m_nCurItem++;
		}
		else {
			return; // New line corresponds to the same tag
		}
	}
	else if (nDiff == -1) {
		if ((m_nCurItem > 0) && 
			(m_arrLines[m_nCurItem]->getLine() > nLine)) {
			m_nCurItem--;
		}
		else {
			return; // New line corresponds to the same tag
		}
	}
	else {
		// Initialise binary search
		nFrom = 0;
		nTo = m_nItems - 1;
		m_nCurItem = 0; // use the first item if nothing else works
		
		// Perform a binary search
		// This algorithm finds the greatest line that is smaller or equal to
		// the requested line
		do {
			nItem = (nFrom + nTo) / 2;
			pItem = m_arrLines[nItem];
			
			if (pItem->getLine() == nLine) {
				m_nCurItem = nItem;
				break;
			}
			else if (nLine > pItem->getLine()) {
				m_nCurItem = nItem;
				nFrom = nItem + 1;
			}
			else {
				nTo = nItem - 1;
			}
		} while (nFrom <= nTo);
	}
		
	// Mark the selected item
	pItem = m_arrLines[m_nCurItem];
	m_pList->setCurrentItem(pItem);
	
	m_nPendLine = 0;
}

/**
 * Deletes all items in the list.
 */
void CtagsList::clear()
{
	m_pList->clear();
	m_nItems = 0;
	m_nCurItem = 0;
	m_nCurLine = 0;
	m_nPendLine = 0;
	m_bReady = false;
}

/**
 * Indicates Ctags has finished processing the current file.
 * If a goto operation has been scheduled, it is processed.
 * @param	nRecords	The number of records generated by Ctags
 */
void CtagsList::slotCtagsFinished(uint nRecords)
{
	if (nRecords) {
		m_bReady = true;
		if (m_nPendLine)
			gotoLine(m_nPendLine);
	}
}

/**
 * Determines the new sort order in the tags list.
 * This slot is connected to the clicked() signal of the tag list's header.
 * @param	nSection	Identifies the column whose header button was clicked.
 */
void CtagsList::slotSortChanged(int nSection)
{
	// Determine whether the new order is ascending or descending
    QHeaderView *pHeader = (QHeaderView *)m_pList->headerItem();
    Qt::SortOrder order = pHeader->sortIndicatorOrder(); 
	
	// Translate the section number into the order constant
	switch (nSection) {
	case HEADER_NAME:
		// Sort by name
		Config().setCtagSortOrder(order == Qt::AscendingOrder ?
			KScopeConfig::NameAsc : KScopeConfig::NameDes);
		break;
		
	case HEADER_LINE:
		// Sort by line
		Config().setCtagSortOrder(order == Qt::AscendingOrder ?
			KScopeConfig::LineAsc : KScopeConfig::LineDes);
		break;
		
	case HEADER_TYPE:
		// Sort by type
		Config().setCtagSortOrder(order == Qt::AscendingOrder ?
			KScopeConfig::TypeAsc : KScopeConfig::TypeDes);
		break;
	}
}

#include "ctagslist.moc"
