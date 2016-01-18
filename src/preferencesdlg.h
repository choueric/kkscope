#ifndef PREFERENCESDLG_H
#define PREFERENCESDLG_H

#include <QWidget>
#include <kpagedialog.h>

class PrefFrontend;
class PrefColor;
class PrefFont;
class PrefOpt;

/**
 * The main configuration dialog for KScope.
 * This dialog displays a set of configuration pages, each dedicated to a
 * different subject (frontend programme paths, colours, etc.)
 * This code is based on a tutorial by Andreas Nicolai which can be found at
 * http://www.kdevelop.org/doc/tutorial_settings
 * @author Elad Lahav
 */

class PreferencesDlg : public KPageDialog
{
   Q_OBJECT

public: 
	PreferencesDlg(QWidget* pParent = 0, uint nPage = Frontend);
	~PreferencesDlg();

	/** Available pages. */
	enum { Frontend = 0, Colors, Fonts, Options };

signals:
	/**
	 * Emitted when the global configuration changes as a result of using
	 * this dialogue.
	 */
	void applyPref();

protected slots:
	virtual void accept();
	virtual void slotApply();
	virtual void slotDefault();
	
private:
	/** The front-end programmes page. */
	PrefFrontend* m_pPrefFrontend;
	
	/** The colours preference page. */
	PrefColor* m_pPrefColor;
	
	/** The fonts preference page. */
	PrefFont* m_pPrefFont;
	
	/** The additional options page. */
	PrefOpt* m_pPrefOpt;
	
	void loadConfig();
	bool updateConfig();
	bool verifyPaths();

private slots:
	void slotModified();
};

#endif
