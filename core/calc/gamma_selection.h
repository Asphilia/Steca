//  ***********************************************************************************************
//
//  Steca: stress and texture calculator
//
//! @file      core/calc/gamma_selection.h
//! @brief     Defines GammaSelection
//!
//! @homepage  https://github.com/scgmlz/Steca
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016-2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, MAINTAINER)
//
//  ***********************************************************************************************

#ifndef GAMMA_SELECTION_H
#define GAMMA_SELECTION_H

#include "qcr/engine/cell.h"
#include <QObject>

//! Supports different ways of setting a gamma range.

class GammaSelection : public QObject {
public:
    GammaSelection();

    void fromJson(const JsonObj& obj);
    void onData();

    void selectSlice(int);
    void setRange(const Range&);

    const Range& range() const { return range_; }
    Range slice2range(int) const;
    double min() const { return range_.min; }
    double max() const { return range_.max; }
    ParamCell<int> numSlices {1};
    int idxSlice() const { return iSlice_; }
    QJsonObject toJson() const;

private:
    void recomputeCache();
    Range fullRange_;
    Range range_;
    int iSlice_ {0};
};

#endif // GAMMA_SELECTION_H
