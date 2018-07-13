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

#include "qcr/engine/param_wrapper.h"
#include <QObject>

//! Supports different ways of setting a gamma range.

class GammaSelection : public QObject {
public:
    GammaSelection();

    void fromJson(const JsonObj& obj);
    void setRange(const Range&);
    void onData();

    QJsonObject toJson() const;
    const Range& range() const { return range_; }
    Range slice2range(int) const;
    double min() const { return range_.min; }
    double max() const { return range_.max; }

    ParamWrapper<int> numSlices {1};
    ParamWrapper<int> currSlice {1}; // counting from 1, for user convenience

private:
    void recomputeCache();
    Range fullRange_;
    Range range_;
};

#endif // GAMMA_SELECTION_H
