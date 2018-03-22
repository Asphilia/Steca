// ************************************************************************** //
//
//  Steca: stress and texture calculator
//
//! @file      gui/dialogs/exportfile_dialogfield.h
//! @brief     Defines class ExportfileDialogfield
//!
//! @homepage  https://github.com/scgmlz/Steca
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016-2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, MAINTAINER)
//
// ************************************************************************** //

#ifndef EXPORTFILE_DIALOGFIELD_H
#define EXPORTFILE_DIALOGFIELD_H

#include "gui/base/controls.h"

//! Base class for dialogs for saving some output to a file.

class ExportfileDialogfield : public QHBoxLayout {
public:
    ExportfileDialogfield(QWidget* parent, bool withTypes);
    QString filePath(bool withSuffix, bool withNumber=false);
    QString separator() const;
private:
    QLineEdit* dir_;
    QLineEdit* file_;
};

#endif // EXPORTFILE_DIALOGFIELD_H
