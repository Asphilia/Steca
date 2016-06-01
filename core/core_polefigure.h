// ************************************************************************** //
//
//  STeCa2:    StressTexCalculator ver. 2
//
//! @file      core_polefigure.h
//! @brief     Pole figure
//!
//! @homepage  http://apps.jcns.fz-juelich.de/steca2
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Antti Soininen, Jan Burle, Rebecca Brydon
//! @authors   Based on the original STeCa by Christian Randau
//
// ************************************************************************** //

#ifndef CORE_POLEFIGURE_H
#define CORE_POLEFIGURE_H

#include "core_reflection_info.h"
#include "types/core_angles.h"

class Progress;

namespace core { namespace pole {
//------------------------------------------------------------------------------

ReflectionInfos interpolate(ReflectionInfos const&, deg alphaStep, deg betaStep,
                            deg averagingAlphaMax, deg averagingRadius,
                            deg idwRadius, qreal inclusionTreshold);
uint numAlphas(deg step);
uint numBetas(deg step);

//------------------------------------------------------------------------------
}}
#endif  // CORE_POLEFIGURE_H
