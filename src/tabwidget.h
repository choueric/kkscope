#ifndef TABWIDGET_H
#define TABWIDGET_H


#include <qtoolbutton.h>
#include <QMenu>
#include <QLabel>
#include <ktabwidget.h>

/**
 * An extension to the standard KDE tab widget that allows the user to select
 * a tab from a list displayed as a popup menu.
 * @author Elad Lahav
 */
class TabWidget : public KTabWidget
{
Q_OBJECT
public:
    TabWidget(QWidget* pParent = 0);
    ~TabWidget();

private:
	/** The list button. */
	QToolButton* m_pButton;

    /** shortcut tip text. */
    QLabel* m_label;
	
	/** A popup-menu containing all tab labels. */
	QMenu* m_pMenu;
	
private slots:
	void slotShowTabList();
	void setCurrentTab(QAction *);
};

#endif
