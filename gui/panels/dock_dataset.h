// ************************************************************************** //
//
//  Steca: stress and texture calculator
//
//! @file      gui/panels/dock_dataset.h
//! @brief     Defines class ViewDatasets
//!
//! @homepage  https://github.com/scgmlz/Steca
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016-2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, MAINTAINER)
//
// ************************************************************************** //

#ifndef DOCK_DATASET_H
#define DOCK_DATASET_H

#include "widgets/various_widgets.h"

class QSpinBox;

//! Part of the main window that controls the dataset selection.

//! Shows the datasets in the selected files, and allow to select some of them
//! and to combine them by a constant factor

class ViewDatasets : public DockWidget {
public:
    ViewDatasets();
    QSpinBox* combineDatasets_;

private:
    class DatasetView* dataseqView_;
};

#endif // DOCK_DATASET_H
