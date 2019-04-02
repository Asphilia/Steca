//  ***********************************************************************************************
//
//  Steca: stress and texture calculator
//
//! @file      devtools/numdiff.h
//! @brief     Defines function readFile
//!
//! @homepage  https://github.com/scgmlz/Steca
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016-2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, MAINTAINER)
//
//  ***********************************************************************************************

#ifndef NUMDIFF_H
#define NUMDIFF_H

#include <string>

namespace numdiff {

bool compareFiles(std::string, std::string, double);

}

#endif //NUMDIFF_H
