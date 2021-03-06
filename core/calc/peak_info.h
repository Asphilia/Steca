//  ***********************************************************************************************
//
//  Steca: stress and texture calculator
//
//! @file      core/calc/peak_info.h
//! @brief     Defines class PeakInfo
//!
//! @homepage  https://github.com/scgmlz/Steca
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016-2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, MAINTAINER)
//
//  ***********************************************************************************************

#ifndef PEAK_INFO_H
#define PEAK_INFO_H

#include "core/base/angles.h"
#include "core/typ/range.h"

class Metadata;
class OnePeakSettings;

//! Metadata, peak fit results, and pole figure angles.

class PeakInfo final {
public:
    PeakInfo(const Metadata*,
             deg alpha, deg beta, Range, double, double /*error*/,
             deg, deg /*error*/, double, double /*error*/, double, double /*error*/);
    // used all_infos.cpp 70
    PeakInfo(deg alpha, deg beta, Range, double, double /*error*/, deg, deg /*error*/,
             double, double /*error*/); // used interpolate_polefig.cpp 314, 329
    PeakInfo(const Metadata*, deg alpha, deg beta, Range);
    PeakInfo(deg alpha, deg beta);
    PeakInfo(const PeakInfo&) = delete;
    PeakInfo(PeakInfo&&) = default;

    deg alpha() const { return alpha_; }
    deg beta() const { return beta_; }
    Range rgeGma() const { return rgeGma_; }
    double inten() const { return inten_; }
    deg tth() const { return tth_; }
    double fwhm() const { return fwhm_; }
    double gammOverSigma() const { return gammOverSigma_; }
    std::vector<QVariant> peakData() const;

private:
    const Metadata*const md_;
    deg alpha_, beta_;
    Range rgeGma_;
    double inten_, intenError_;
    deg tth_, tthError_;
    double fwhm_, fwhmError_;
    double gammOverSigma_, gammOverSigmaError_;
};

#endif // PEAK_INFO_H
