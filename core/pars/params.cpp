//  ***********************************************************************************************
//
//  Steca: stress and texture calculator
//
//! @file      core/pars/params.cpp
//! @brief     Implements class Params
//!
//! @homepage  https://github.com/scgmlz/Steca
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016-2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, MAINTAINER)
//
//  ***********************************************************************************************

#include "params.h"
#include "core/session.h"

Params::Params()
{
    intenScaledAvg.setHook([](bool){ gSession->onNormalization(); });; // if not, summed
    intenScale.setHook([](double){ gSession->onNormalization(); });;
    howtoNormalize.setHook([](int){ gSession->onNormalization(); });
}
