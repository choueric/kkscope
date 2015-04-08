#include <qcheckbox.h>
#include <qradiobutton.h>
#include <qlineedit.h>
#include <qlabel.h>
#include "prefopt.h"
#include "kscopeconfig.h"

/**
 * Class constructor.
 * @param	pParent	The parent widget
 * @param	szName	The widget's name
 */
PrefOpt::PrefOpt(QWidget* pParent)
{
    setupUi(this);
	// Set initial values
	load();
		
	// Emit the "modified" signal whenever any of the widgets changes its
	// its. This will notify the parent dialogue to enable its "Apply"
	// button
	connect(m_pReadOnlyCheck, SIGNAL(toggled(bool)), this, 
		SIGNAL(modified()));
	connect(m_pLastProjCheck, SIGNAL(toggled(bool)), this, 
		SIGNAL(modified()));
	connect(m_pTagHlCheck, SIGNAL(toggled(bool)), this, 
		SIGNAL(modified()));
	connect(m_pBriefQueryCaptCheck, SIGNAL(toggled(bool)), this, 
		SIGNAL(modified()));
	connect(m_pWarnModifiedOnDiskCheck, SIGNAL(toggled(bool)), this, 
		SIGNAL(modified()));
	connect(m_pAutoSortCheck, SIGNAL(toggled(bool)), this, 
		SIGNAL(modified()));
	connect(m_pExtEditorEdit, SIGNAL(textChanged(const QString&)), this,
		SIGNAL(modified()));
	connect(m_pSysProfileCB, SIGNAL(activated(int)), this,
		SIGNAL(modified()));
	connect(m_pEditorPopupCB, SIGNAL(activated(int)), this,
		SIGNAL(modified()));
}

/**
 * Class destructor.
 */
PrefOpt::~PrefOpt()
{
}

/**
 * Reads the current settings from the configuration object, and applies them
 * the the page's widget.
 */
void PrefOpt::load()
{
	m_pReadOnlyCheck->setChecked(Config().getReadOnlyMode());
	m_pLastProjCheck->setChecked(Config().getLoadLastProj());
	m_pTagHlCheck->setChecked(Config().getAutoTagHl());
	m_pBriefQueryCaptCheck->setChecked(Config().getUseBriefQueryCaptions());
	m_pWarnModifiedOnDiskCheck->setChecked(Config().getWarnModifiedOnDisk());
	m_pAutoSortCheck->setChecked(Config().getAutoSortFiles());
	m_pExtEditorEdit->setText(Config().getExtEditor());
	
	switch (Config().getSysProfile()) {
	case KScopeConfig::Fast:
		m_pSysProfileCB->setCurrentIndex(0);
		break;
		
	case KScopeConfig::Slow:
		m_pSysProfileCB->setCurrentIndex(1);
		break;
	}
	
	switch (Config().getEditorPopup()) {
	case KScopeConfig::Embedded:
		m_pEditorPopupCB->setCurrentIndex(0);
		break;
		
	case KScopeConfig::KScopeOnly:
		m_pEditorPopupCB->setCurrentIndex(1);
		break;
	}		
}

/**
 * Commits settings changes to the configuration object.
 */
void PrefOpt::apply()
{
	Config().setReadOnlyMode(m_pReadOnlyCheck->isChecked());
	Config().setLoadLastProj(m_pLastProjCheck->isChecked());
	Config().setAutoTagHl(m_pTagHlCheck->isChecked());
	Config().setUseBriefQueryCaptions(m_pBriefQueryCaptCheck->isChecked());
	Config().setWarnModifiedOnDisk(m_pWarnModifiedOnDiskCheck->isChecked());
	Config().setAutoSortFiles(m_pAutoSortCheck->isChecked());
	Config().setExtEditor(m_pExtEditorEdit->text());
	
	switch (m_pSysProfileCB->currentIndex()) {
	case 0 :
		Config().setSysProfile(KScopeConfig::Fast);
		break;
		 
	case 1:
		Config().setSysProfile(KScopeConfig::Slow);
		break;
	}
	
	switch (m_pEditorPopupCB->currentIndex()) {
	case 0:
		Config().setEditorPopup(KScopeConfig::Embedded);
		break;
		
	case 1:
		Config().setEditorPopup(KScopeConfig::KScopeOnly);
		break;
	}
}

#include "prefopt.moc"
