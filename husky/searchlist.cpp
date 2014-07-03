/***************************************************************************
 *
 * Copyright (C) 2005 Elad Lahav (elad_lahav@users.sourceforge.net)
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ***************************************************************************/

#include <QKeyEvent>
#include <QHeaderView>
#include "searchlist.h"

/**
 * Intercepting additional key events of QLineEdit to browse the list
 * @param	pKey	The pressed key event
 */
void SearchLineEdit::keyPressEvent(QKeyEvent* pKey) 
{
	switch(pKey->key()) {
	case Qt::Key_Up:
	case Qt::Key_Down:
	case Qt::Key_PageUp:
	case Qt::Key_PageDown:
		emit keyPressed(pKey); 
		break;
	
	default:
		QLineEdit::keyPressEvent(pKey);
		break;
	}
}
	

/**
 * Class constructor.
 * @param	nSearchCol	The list column on which to perform string look-ups
 * @param	pParent		The parent widget
 * @param	szName		The widget's name
 */
SearchList::SearchList(int nSearchCol, QWidget* pParent, const char* szName) :
    QWidget(pParent),
	m_nSearchCol(nSearchCol)
{
	// Create the child widgets
	m_pEdit = new SearchLineEdit(this);
	m_pList = new QListWidget(this);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_pEdit);
    layout->addWidget(m_pList);
    this->setLayout(layout);
	
	connect(m_pEdit, SIGNAL(textChanged(const QString&)), this,
		SLOT(slotFindItem(const QString&)));
	connect(m_pList, SIGNAL(doubleClicked(QListWidgetItem*)), this,
		SLOT(slotItemSelected(QListWidgetItem*)));
	connect(m_pList, SIGNAL(returnPressed(QListWidgetItem*)), this,
		SLOT(slotItemSelected(QListWidgetItem*)));
	connect(m_pEdit, SIGNAL(returnPressed()), this,
		SLOT(slotItemSelected()));
	connect(m_pEdit, SIGNAL(keyPressed(QKeyEvent*)), this,
		SLOT(slotKeyPressed(QKeyEvent*)));
}

/**
 * Class destructor.
 */
SearchList::~SearchList()
{
}

/**
 * Sets the keyboad focus to the search box.
 */
void SearchList::slotSetFocus()
{
	m_pEdit->setFocus();
}

/**
 * Selects a list item whose string begins with the text entered in the edit
 * widget.
 * This slot is connected to the textChanged() signal of the line edit widget.
 * @param	sText	The new text in the edit widget
 */
void SearchList::slotFindItem(const QString& sText)
{
	QList<QListWidgetItem *> items;
	
	// Try to find an item that contains this text
	// Priority to exactly matched, 
	// then try to find line begins with the text,
	// and if not found, then try to find the line contains the text
	items = m_pList->findItems(sText, 
            Qt::MatchExactly | Qt::MatchStartsWith| Qt::MatchContains);

	// Select this item
	if (!items.isEmpty()) {
		m_pList->setCurrentItem(items.first(), QItemSelectionModel::Select);
		m_pList->scrollToItem(items.first());
	}
}

/**
 * Lets inheriting classes process an item selection made through the list 
 * widget.
 * This slot is connected to the doubleClicked() and returnPressed()
 * signals of the list widget.
 */
void SearchList::slotItemSelected(QListWidgetItem* pItem)
{
	processItemSelected(pItem);
	m_pEdit->setText("");
}

/**
 * Lets inheriting classes process an item selection made through the edit 
 * widget.
 * This slot is connected to the returnPressed() signal of the edit widget.
 */
void SearchList::slotItemSelected()
{
	QListWidgetItem* pItem;

	if ((pItem = m_pList->currentItem()) != NULL) {
		m_pEdit->setText(pItem->text());
		processItemSelected(pItem);
	}
	
	m_pEdit->setText("");
}

#define SEARCH_MATCH(pItem) \
	pItem->text().startsWith(m_pEdit->text())

/**
 * Sets a new current item based on key events in the edit box.
 * This slot is connected to the keyPressed() signal of the edit widget.
 * @param	pKey	The key evant passed by the edit box
 */
void SearchList::slotKeyPressed(QKeyEvent* pKey)
{
	QListWidgetItem* pItem, * pNewItem;
	int nPageSize, nPos;

	// Select the current item, or the first one if there is no current item
	pItem = m_pList->currentItem();
		
	// Set a new current item based on the pressed key
	switch (pKey->key()) {
	case  Qt::Key_Up:
		if (pItem) {
            do {
                int row = m_pList->row(pItem);
                pNewItem = m_pList->item(row - 1);
            } while (pNewItem && !SEARCH_MATCH(pNewItem));

			if (pNewItem)
				pItem = pNewItem;
		}
		break;
		
	case  Qt::Key_Down:
		if (pItem) {
            do {
                int row = m_pList->row(pItem);
                pNewItem = m_pList->item(row + 1);
            } while (pNewItem && !SEARCH_MATCH(pNewItem));

			if (pNewItem)
				pItem = pNewItem;
		}
		break;
	
        // TODO
#if 0
	case  Qt::Key_PageUp:
		nPageSize = m_pList->visibleHeight() / pItem->height();
		for (nPos = 0; 
			pItem && pItem->itemAbove() && (nPos < nPageSize); 
			nPos++)
			pItem = pItem->itemAbove();
		break;
		
	case  Qt::Key_PageDown:
		nPageSize = m_pList->visibleHeight() / pItem->height();
		for (nPos = 0; 
			pItem && pItem->itemBelow() && (nPos < nPageSize); 
			nPos++)
			pItem = pItem->itemBelow();
		break;
#endif
	
	default:
		pKey->ignore();
		return;
	}

	// Select the first item if no other item was selected
	if (pItem == NULL)
		pItem = m_pList->item(1); // TODO: the first row is 0 or 1 ?
		
	// Select the new item
	if (pItem) {
		m_pList->setCurrentItem(pItem);
		m_pList->scrollToItem(pItem);
	}
}

#include "searchlist.moc"
