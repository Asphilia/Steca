// ************************************************************************** //
//
//  Steca: stress and texture calculator
//
//! @file      gui/panels/dock_metadata.h
//! @brief     Defines class ViewMetadata
//!
//! @homepage  https://github.com/scgmlz/Steca
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016-2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, MAINTAINER)
//
// ************************************************************************** //

#ifndef DOCK_METADATA_H
#define DOCK_METADATA_H

#include "widgets/various_widgets.h"

//! Part of the main window that shows the metadata of the selected dataset
class ViewMetadata : public DockWidget {
public:
    ViewMetadata();
private:
    class MetadataView* metadataView_;
};

#endif // DOCK_METADATA_H
