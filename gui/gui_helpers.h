// ************************************************************************** //
//
//  Steca2: stress and texture calculator
//
//! @file      gui/gui_helpers.h
//! @brief     Defines ...
//!
//! @homepage  https://github.com/scgmlz/Steca2
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ (see CITATION, MAINTAINER)
//
// ************************************************************************** //

#ifndef GUI_HELPERS_H
#define GUI_HELPERS_H

#include "typ/str.h"
#include <QCheckBox>
#include <QComboBox>
#include <QDockWidget>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QRadioButton>
#include <QSpinBox>
#include <QToolButton>
#include <QTreeView>

// make connects shorter

#define slot(Type, method, parType) static_cast<void (Type::*)(parType)>(&Type::method)

//! layouts

extern int mWidth(QWidget const*);

// handy functions that make (new) widgets

QBoxLayout* boxLayout(Qt::Orientation);
QBoxLayout* hbox(); // horizontal box layout
QBoxLayout* vbox(); // vertical box layout

QGridLayout* gridLayout();

QLabel* label(rcstr);

QLineEdit* editCell(uint emWidth); // emWidth: measured in typographical (m)s
QLineEdit* readCell(uint emWidth);

QSpinBox* spinCell(uint emWidth, int min = INT_MIN, int max = INT_MAX);
QDoubleSpinBox* spinDoubleCell(uint emWidth, qreal min = LLONG_MIN, qreal max = LLONG_MAX);

QCheckBox* check(rcstr text);
QCheckBox* check(QAction*);

QToolButton* textButton(QAction*);
QToolButton* iconButton(QAction*);

QRadioButton* radioButton(rcstr text);

//! abstract tree widget

class TreeView : public QTreeView {
public:
    TreeView();

    int sizeHintForColumn(int) const; // make narrow columns
};

//! abstract tree widget used as a list (hides column 0)

class TreeListView : public TreeView {
public:
    TreeListView();

protected:
    void setModel(QAbstractItemModel*);
};

//! Read-only version of QLineEdit

class LineView : public QLineEdit {
public:
    LineView();

    void setText(rcstr);
};

//! a widget with a box layout

class BoxWidget : public QWidget {
private:
public:
    BoxWidget(Qt::Orientation);

protected:
    QBoxLayout* box_;
};

//! a dock widget that acts as BoxWidget

class DockWidget : public QDockWidget {
private:
public:
    DockWidget(rcstr name, rcstr objectName, Qt::Orientation);

protected:
    QBoxLayout* box_;
};

#endif // GUI_HELPERS_H
