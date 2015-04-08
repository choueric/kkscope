#include <qspinbox.h>
#include "graphprefdlg.h"
#include "preferencesdlg.h"
#include "kscopeconfig.h"

/**
 * Class constructor.
 * @param	pParent	The parent widget
 * @param	szName	The widget's name
 */
GraphPrefDlg::GraphPrefDlg(QWidget* pParent) :
{
    setupUi(this);
	m_pMaxDegSpin->setValue(Config().getGraphMaxNodeDegree());
}

/**
 * Class destructor.
 */
GraphPrefDlg::~GraphPrefDlg()
{
}

/**
 * @return	The maximal degree value set in the spin box
 */
int GraphPrefDlg::getMaxNodeDegree()
{
	return m_pMaxDegSpin->value();
}

/**
 * Displays the general preferences dialogue, showing the "Colours" page.
 * This slot is connected to the clicked() signal of the colours button.
 */
void GraphPrefDlg::slotFontClicked()
{
	PreferencesDlg dlg(PreferencesDlg::Fonts);
	
	dlg.exec();
}

/**
 * Displays the general preferences dialogue, showing the "Fonts" page.
 * This slot is connected to the clicked() signal of the fonts button.
 */
void GraphPrefDlg::slotColorClicked()
{
	PreferencesDlg dlg(PreferencesDlg::Colors);
	
	dlg.exec();
}

#include "graphprefdlg.moc"

