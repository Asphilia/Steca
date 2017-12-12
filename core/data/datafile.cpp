// ************************************************************************** //
//
//  Steca2: stress and texture calculator
//
//! @file      core/data/datafile.cpp
//! @brief     Implements class File
//!
//! @homepage  https://github.com/scgmlz/Steca2
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ (see CITATION, MAINTAINER)
//
// ************************************************************************** //

#include "datafile.h"
#include "typ/str.h"

namespace data {

File::File(rcstr fileName) : fileInfo_(fileName) {}

QFileInfo const& File::fileInfo() const {
    return fileInfo_;
}

str File::fileName() const {
    return fileInfo_.fileName();
}
}