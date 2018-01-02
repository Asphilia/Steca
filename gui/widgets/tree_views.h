// ************************************************************************** //
//
//  Steca2: stress and texture calculator
//
//! @file      gui/widgets/tree_views.h
//! @brief     Defines classes ListView, MultiListView
//!
//! @homepage  https://github.com/scgmlz/Steca2
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ (see CITATION, MAINTAINER)
//
// ************************************************************************** //

#ifndef TREE_VIEWS_H
#define TREE_VIEWS_H

#include "widgets/various_widgets.h"
#include "models.h"

namespace gui {

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

//! A (tree-)list view with a reference to the hub. Single selection.

class ListView : public TreeListView {
public:
    ListView() {}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Woverloaded-virtual"
    // base class has setModel(<other type>*)
    void setModel(models::TableModel* model) { TreeListView::setModel(model); }
#pragma GCC diagnostic pop

protected:
    models::TableModel* model() const {
        return static_cast<models::TableModel*>(TreeListView::model()); }
    void updateSingleSelection();
    void selectRow(int);
};


//! A (tree-)list view with a reference to the hub. Multiple selection.

class MultiListView : public ListView {
public:
    MultiListView();

protected:
    void selectRows(uint_vec);
};

} // namespace gui

#endif // TREE_VIEWS_H
