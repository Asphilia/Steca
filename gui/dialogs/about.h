// ************************************************************************** //
//
//  Steca: stress and texture calculator
//
//! @file      gui/dialogs/about.h
//! @brief     Defines class AboutBox
//!
//! @homepage  https://github.com/scgmlz/Steca
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016-2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, MAINTAINER)
//
// ************************************************************************** //

#ifndef ABOUT_H
#define ABOUT_H

#include "gui/base/controls.h"

//! Modal dialog that informs about the software
class AboutBox : public QDialog {
public:
    AboutBox();
protected:
    QCheckBox *cbShowAtStartup_, *cbCheckUpdatesAtStartup_;
    QDoubleSpinBox *detDistance_, *detPixelSize_;
};

#endif // ABOUT_H