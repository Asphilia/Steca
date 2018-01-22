// ************************************************************************** //
//
//  Steca: stress and texture calculator
//
//! @file      core/data/rawfile.cpp
//! @brief     Implements class Rawfile
//!
//! @homepage  https://github.com/scgmlz/Steca
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016-2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, MAINTAINER)
//
// ************************************************************************** //

#include "core/data/rawfile.h"
#include <QStringBuilder> // for ".." % ..

Rawfile::Rawfile(rcstr fileName) : fileInfo_(fileName) {}

//! The loaders use this function to push cluster
void Rawfile::addDataset(const Metadata& md, size2d const& sz, inten_vec const& ivec) {
    if (measurements_.isEmpty())
        imageSize_ = sz;
    else if (sz != imageSize_)
        THROW("Inconsistent image size in " % fileName());
    measurements_.append(shp_Measurement(new Measurement(measurements_.count(), md, sz, ivec)));
}

QVector<const Measurement*> const Rawfile::measurements() const
{
    QVector<const Measurement*> ret;
    for (const shp_Measurement& one: measurements_)
        ret.append(one.data());
    return ret;
}

QFileInfo const& Rawfile::fileInfo() const {
    return fileInfo_;
}

str Rawfile::fileName() const {
    return fileInfo_.fileName();
}

shp_Image Rawfile::foldedImage() const {
    debug::ensure(!measurements_.isEmpty());
    shp_Image ret(new Image(measurements_.first()->imageSize()));
    for (shp_Measurement one : measurements_)
        ret->addIntens(*one->image());
    return ret;
}