// ************************************************************************** //
//
//  Steca: stress and texture calculator
//
//! @file      gui/state.h
//! @brief     Defines class GuiState
//!
//! @homepage  https://github.com/scgmlz/Steca
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016-2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, MAINTAINER)
//
// ************************************************************************** //

#ifndef STATE_H
#define STATE_H

class GuiState {
public:
    GuiState();
    bool editingBaseline;
    bool editingPeakfits;

    class CCheckBox* polefigShowGridPts;
    class CComboBox* diagramX;
    class CComboBox* diagramY;
};

#endif // STATE_H
