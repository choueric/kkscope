#include <QToolButton>
#include <qtooltip.h>
#include <klocale.h>
#include "tabwidget.h"
#include "kscopepixmaps.h"

/**
 * Class constructor.
 * @param	pParent	A pointer to the parent widget
 * @param	szName	Optional widget name
 */
TabWidget::TabWidget(QWidget* pParent, const char* szName) :
	KTabWidget(pParent)
{
	// Create a menu
	m_pMenu = new QMenu(this);
	
	// Set the current tab based on the menu selection
	connect(m_pMenu, SIGNAL(activated(int)), this, SLOT(setCurrentPage(int)));
	
	// Create a button at the top-right corner of the tab widget
	m_pButton = new QToolButton(this);
	m_pButton->setIcon(Pixmaps().getPixmap(KScopePixmaps::TabList));
	m_pButton->setToolTip(i18n("Shows a list of all open tabs"));
	m_pButton->adjustSize();
	setCornerWidget(m_pButton, Qt::TopRightCorner);
	
	// Show the popup-menu when the button is clicked
	connect(m_pButton, SIGNAL(clicked()), this, SLOT(slotShowTabList()));
}

/**
 * Class destructor.
 */
TabWidget::~TabWidget()
{
}

/**
 * Creates and displays a popup-menu containing all tab labels.
 * This slot is connected to the clicked() signal emitted by the list button.
 */
void TabWidget::slotShowTabList()
{
	int i;
	
	// Delete the previous menu
	m_pMenu->clear();

	// Create and populate the menu	
	for (i = 0; i < count(); i++)
		m_pMenu->addAction(tabText(i));
		
	// Show the menu
	m_pMenu->popup(mapToGlobal(m_pButton->pos()));
}

#include "tabwidget.moc"
