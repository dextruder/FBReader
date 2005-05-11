/*
 * Copyright (C) 2005 Nikolay Pultsin <geometer@mawhrin.net>
 * Copyright (C) 2005 Mikhail Sobolev <mss@mawhrin.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef __GTKOPTIONVIEW_H__
#define __GTKOPTIONVIEW_H__

#include <gtk/gtkwidget.h>

#include "../../abstract/dialogs/ZLOptionsDialog.h"
#include "../../abstract/dialogs/ZLOptionEntry.h"

class GtkOptionsDialogTab;

class GtkOptionView : public OptionView {

protected:
	GtkOptionView(ZLOptionEntry *option, GtkOptionsDialogTab *tab, int row, int fromColumn, int toColumn) : OptionView(option), myTab(tab), myRow(row), myFromColumn(fromColumn), myToColumn(toColumn), myInitialized(false) {}
	GtkOptionView(ZLOptionEntry *option) : OptionView(option), myInitialized(false) {}

public:
	virtual ~GtkOptionView() {}
	void setPosition(GtkOptionsDialogTab *tab, int row, int fromColumn, int toColumn) {
		myTab = tab;
		myRow = row;
		myFromColumn = fromColumn;
		myToColumn = toColumn;
	}

	void setVisible(bool visible) {
		if (visible) {
			if (!myInitialized) _createItem(); myInitialized = true; setActive(myOption->isActive()); _show();
		} else {
			if (myInitialized) _hide();
		}
	}
	void setActive(bool active) {
		if (myInitialized) {
			_setActive(active);
		}
	}
	void onAccept() const { if (myInitialized) _onAccept(); }

public:
	// !!! this function is added for test purposes, should be removed !!!
	void createItem() { if (!myInitialized) _createItem(); myInitialized = true; }
	
protected:
	virtual void _createItem() = 0;
	virtual void _hide() = 0;
	virtual void _show() = 0;
	// TODO: replace by pure virtual method
	virtual void _setActive(bool active) {}
	virtual void _onAccept() const = 0;

protected:
	GtkOptionsDialogTab *myTab;
	int myRow, myFromColumn, myToColumn;

private:
	bool myInitialized;
};

#if 0
class ChoiceOptionView : public GtkOptionView {

public:
	ChoiceOptionView(ZLChoiceOptionEntry *option, GtkOptionsDialogTab *tab, int row, int fromColumn, int toColumn) : GtkOptionView(option, tab, row, fromColumn, toColumn) {
		myButtons = 0;
	}
	~ChoiceOptionView() { if (myButtons != 0) delete[] myButtons; }

protected:
	void _createItem();
	void _show();
	void _hide();
	void _onAccept() const;

private:
	GtkFrame *myFrame;
	QRadioButton **myButtons;
};
#endif

class BooleanOptionView : public GtkOptionView {

public:
	BooleanOptionView(ZLBooleanOptionEntry *option, GtkOptionsDialogTab *tab, int row, int fromColumn, int toColumn) : GtkOptionView(option, tab, row, fromColumn, toColumn) {}

protected:
	void _createItem();
	void _show();
	void _hide();
	void _onAccept() const;

private:
	GtkWidget *myCheckBox;
};

class StringOptionView : public GtkOptionView {

public:
	StringOptionView(ZLStringOptionEntry *option, GtkOptionsDialogTab *tab, int row, int fromColumn, int toColumn) : GtkOptionView(option, tab, row, fromColumn, toColumn) {}

protected:
	void _createItem();
	void _show();
	void _hide();
	void _onAccept() const;

private:
	GtkWidget *myLabel, *myLineEdit;
};

class SpinOptionView : public GtkOptionView {

public:
	SpinOptionView(ZLSpinOptionEntry *option, GtkOptionsDialogTab *tab, int row, int fromColumn, int toColumn) : GtkOptionView(option, tab, row, fromColumn, toColumn) {}

protected:
	void _createItem();
	void _show();
	void _hide();
	void _onAccept() const;

private:
	GtkWidget *myLabel, *mySpinBox;
};

class ComboOptionView : public GtkOptionView {

public:
	ComboOptionView(ZLComboOptionEntry *option, GtkOptionsDialogTab *tab, int row, int fromColumn, int toColumn) : GtkOptionView(option, tab, row, fromColumn, toColumn) {}

protected:
	void _createItem();
	void _show();
	void _hide();
	void _setActive(bool active);
	void _onAccept() const;

private:
	void onValueChange(void);

	static void _onValueChange (GtkWidget *, gpointer);
	
private:
	GtkWidget *myLabel, *myComboBox;
};

class ColorOptionView : public GtkOptionView {

public:
	ColorOptionView(ZLColorOptionEntry *option, GtkOptionsDialogTab *tab, int row, int fromColumn, int toColumn) : GtkOptionView(option, tab, row, fromColumn, toColumn), myColorSelectionDialog(NULL) {}

	virtual ~ColorOptionView(void) {
		if (myColorSelectionDialog != NULL) {
			gtk_widget_destroy (myColorSelectionDialog);
		}
	}

protected:
	void _createItem();
	void _show();
	void _hide();
	void _onAccept() const;

private:
	void onChangeColor();

	static void _onChangeColor(GtkWidget *, gpointer);

private:
	GtkWidget *myWidget, *myColorSelectionDialog, *myDrawingArea;
	GdkColor myColor;
};

#endif /* __GTKOPTIONVIEW_H__ */

// vim:ts=2:sw=2:noet
