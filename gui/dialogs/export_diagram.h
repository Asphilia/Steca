//  ***********************************************************************************************
//
//  Steca: stress and texture calculator
//
//! @file      gui/dialogs/export_diagram.h
//! @brief     Defines class ExportDiagram
//!
//! @homepage  https://github.com/scgmlz/Steca
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016-2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, MAINTAINER)
//
//  ***********************************************************************************************

#ifndef EXPORT_DIAGRAM_H
#define EXPORT_DIAGRAM_H

#include "gui/dialogs/dialog_save.h"

//! The modal dialog for the data shown in the diagram

class ExportDiagram : public DialogSave {
public:
    ExportDiagram();
private:
    void writeCurrent(QTextStream&) final;
};

#endif // EXPORT_DIAGRAM_H
