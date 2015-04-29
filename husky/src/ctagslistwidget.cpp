#include "husky.h"

#include <KLocale>
#include "ctagslistwidget.h"
#include "kscopeconfig.h"
#include "kscopepixmaps.h"

#define HEADER_COUNT 3
#define HEADER_NAME 0
#define HEADER_LINE 1
#define HEADER_TYPE 2

/**
 * Class constructor.
 * @param	pParent	The parent widget
 * @param	szName	The widget's name
 */
CtagsListWidget::CtagsListWidget(QWidget* pParent) :
	SearchListView(HEADER_NAME, pParent),
	m_nItems(0),
	m_nCurItem(0),
	m_bReady(false),
	m_nCurLine(0),
	m_nPendLine(0)
{
    m_pModel = new StringListModel(HEADER_COUNT, this);
    QStringList header;
    header << i18n("Name") << i18n("Line") << i18n("Type");
    m_pModel->setHeader(header);
    setSourceModel(m_pModel);

    m_pView->header()->setResizeMode(QHeaderView::ResizeToContents);

	connect(m_pView->header(), SIGNAL(sectionClicked(int)), this,
		SLOT(slotSortChanged(int)));

	// Determine the default sorting order
	switch (Config().getCtagSortOrder()) {
	case KScopeConfig::NameAsc:
		m_pView->sortByColumn(HEADER_NAME, Qt::AscendingOrder);
		break;
	case KScopeConfig::NameDes:
		m_pView->sortByColumn(HEADER_NAME, Qt::DescendingOrder);
		break;
	case KScopeConfig::LineAsc:
		m_pView->sortByColumn(HEADER_LINE, Qt::AscendingOrder);
		break;
	case KScopeConfig::LineDes:
		m_pView->sortByColumn(HEADER_LINE, Qt::DescendingOrder);
		break;
	case KScopeConfig::TypeAsc:
		m_pView->sortByColumn(HEADER_TYPE, Qt::AscendingOrder);
		break;
	case KScopeConfig::TypeDes:
		m_pView->sortByColumn(HEADER_TYPE, Qt::DescendingOrder);
		break;
	}

	// Set colours and font
	applyPrefs();
}

/**
 * Class destructor.
 */
CtagsListWidget::~CtagsListWidget()
{
}

/**
 * Adds a Ctags output entry to the list.
 * This slot is connected to the dataReady() signal of a CtagsFrontend object.
 * @param	pToken	The first token in the entry
 */
void CtagsListWidget::slotDataReady(FrontendToken* pToken)
{
	QString sName, sType, sLine;
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
    int row = 0;
    QStringList itemList;
    itemList << sName << sLine << sType;
    m_pModel->addItem(itemList, row);

    QIcon icon(Pixmaps().getPixmap(pix));
	m_pModel->setIcon(row, HEADER_NAME, icon);
	m_nItems++;
}

/**
 * Handles the "resize" event, which occurs when the size of the widget
 * changes.
 * @param	pEvent	The event data
 */
void CtagsListWidget::resizeEvent(QResizeEvent* pEvent)
{
	SearchListView::resizeEvent(pEvent);
	emit resized();
}

/**
 * Emits the lineRequested() signal when a list item is selected.
 * This function is called if either an item is double-clicked, or an item is
 * highlighted and the ENTER key is pressed.
 * @param	pItem	The selected list item
 */
void CtagsListWidget::processItemSelected(const QModelIndex &index)
{
	QString sLine;
    QModelIndex newIndex = m_proxyModel->index(index.row(), HEADER_LINE);
    sLine = m_proxyModel->data(newIndex).toString();

	emit lineRequested(sLine.toUInt());
}

/**
 * Constructs a tool-tip for the given item.
 * @param	pItem	The item for which a tip is required
 * @param	sTip	The constructed tip string (on return)
 * @return	Always true
 */
bool CtagsListWidget::getTip(QModelIndex &index, QString& sTip)
{
    int row = index.row();
    QModelIndex newIndex;
    QString sType, sName, sLine;
    
    newIndex = m_proxyModel->index(row, HEADER_TYPE);
    sType = m_proxyModel->data(newIndex).toString();

    newIndex = m_proxyModel->index(row, HEADER_NAME);
    sName = m_proxyModel->data(newIndex).toString();

    newIndex = m_proxyModel->index(row, HEADER_LINE);
    sLine = m_proxyModel->data(newIndex).toString();

	sTip = QString("Type: <b>%1</b><br>Name: <b>%2</b><br>Line: <b>%3</b>").
		arg(sType).arg(sName).arg(sLine);
	return true;
}

/**
 * Sets the list's colours and font, according the user's preferences.
 */
void CtagsListWidget::applyPrefs()
{
	// Apply colour settings
    QPalette pe = m_pView->palette();
    pe.setColor(QPalette::Background, Config().getColor(KScopeConfig::TagListBack));
    pe.setColor(QPalette::Foreground, Config().getColor(KScopeConfig::TagListFore));
    m_pView->setPalette(pe);

	m_pView->setFont(Config().getFont(KScopeConfig::TagList));
}

/**
 * Selects the symbol that dominates the given line in the source file.
 * @param	nLine	The requested line
 */
void CtagsListWidget::gotoLine(uint nLine)
{
	// Wait until Ctags finishes
	if (!m_bReady) {
		m_nPendLine = nLine;
		return;
	}		
	
	// Do nothing if no tags are available
	if (m_nItems == 0)
		return;

    //m_pEdit->setText("");
    QString sLine;
    sLine.setNum(nLine);
    QList<QStandardItem *> l;
    l = m_pModel->findItems(sLine, Qt::MatchExactly, HEADER_LINE);

    if (l.isEmpty())
        return;

    QStandardItem *pItem = l[0];
    m_pView->setCurrentIndex(pItem->index());
	
	m_nPendLine = 0;
}

/**
 * Deletes all items in the list.
 */
void CtagsListWidget::clear()
{
    m_pModel->removeRows(0, m_pModel->rowCount());
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
void CtagsListWidget::slotCtagsFinished(uint nRecords)
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
void CtagsListWidget::slotSortChanged(int nSection)
{
    // TODO: Line column cann't sort rightly
	// Determine whether the new order is ascending or descending
    QHeaderView *pHeader = m_pView->header();
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
