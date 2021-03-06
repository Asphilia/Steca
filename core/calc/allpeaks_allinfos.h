//  ***********************************************************************************************
//
//  Steca: stress and texture calculator
//
//! @file      core/calc/allpeaks_allinfos.h
//! @brief     Defines class AllInfos
//!
//! @homepage  https://github.com/scgmlz/Steca
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016-2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, MAINTAINER)
//
//  ***********************************************************************************************

#ifndef ALLPEAKS_ALLINFOS_H
#define ALLPEAKS_ALLINFOS_H

#include "core/calc/onepeak_allinfos.h"
#include "core/typ/lazy_data.h"

//! Direct and interpolated InfoSequence for all Bragg peaks.

class AllPeaksAllInfos {
public:
    AllPeaksAllInfos();
    AllPeaksAllInfos(const AllPeaksAllInfos&) = delete;
    const OnePeakAllInfos* currentDirect() const;
    const OnePeakAllInfos* currentInterpolated() const;
    const OnePeakAllInfos* currentInfoSequence() const;
    const OnePeakAllInfos* At(int) const;
    const std::vector<const OnePeakAllInfos*> allInfoSequences() const;
    void invalidateAll() const;
    void invalidateInterpolated() const;
    void invalidateAt(int) const;
private:
    const std::vector<const OnePeakAllInfos*> allDirect() const;
    const std::vector<const OnePeakAllInfos*> allInterpolated() const;
    mutable lazy_data::VectorCache<OnePeakAllInfos,const AllPeaksAllInfos*> direct;
    mutable lazy_data::VectorCache<OnePeakAllInfos,const AllPeaksAllInfos*> interpolated;
};

#endif // ALLPEAKS_ALLINFOS_H
