//  ***********************************************************************************************
//
//  Steca: stress and texture calculator
//
//! @file      core/peakfit/raw_outcome.cpp
//! @brief     Implements class RawOutcome
//!
//! @homepage  https://github.com/scgmlz/Steca
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016-2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, MAINTAINER)
//
//  ***********************************************************************************************

#include "core/peakfit/raw_outcome.h"
#include "core/typ/curve.h"
#include "qcr/base/debug.h"
#include <qmath.h>

//! Computes raw peak characteristics.

//! Given curve should be restricted to peak range, and corrected for background fit.

RawOutcome::RawOutcome(const Curve& curve)
{
    int n = curve.size();
    if (n <= 0)
        return; // all members are default initialized to Q_QNAN
    intensity_ = 0;
    center_ = 0;
    double stdv = 0; // TODO compute stdv in one pass
    for (int i=0; i<n; ++i) {
        double x = curve.x(i);
        double y = curve.y(i);
        intensity_ += y;
        center_ += x*y;
        stdv += x*x*y;
    }
    center_ /= intensity_;
    stdv = sqrt( stdv/intensity_ - center_*center_ );
    fwhm_ = sqrt(8*log(2))*stdv;
    intensity_ *= curve.rgeX().width() / curve.size();
}
