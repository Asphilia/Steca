// ************************************************************************** //
//
//  Steca2: stress and texture calculator
//
//! @file      core/data/datafile.cpp
//! @brief     Implements class Datafile
//!
//! @homepage  https://github.com/scgmlz/Steca2
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ (see CITATION, MAINTAINER)
//
// ************************************************************************** //

#include "datafile.h"
#include "typ/exception.h"
#include "measurement.h"
#include <QStringBuilder> // for ".." % ..

Datafile::Datafile(rcstr fileName) : fileInfo_(fileName) {}

//! The loaders use this function to push datasequence
void Datafile::addDataset(Metadata const& md, size2d const& sz, inten_vec const& ivec) {
    if (datasequence_.isEmpty())
        imageSize_ = sz;
    else if (sz != imageSize_)
        THROW("Inconsistent image size in " % fileName());
    datasequence_.append(QSharedPointer<Measurement const>(new Measurement(md, sz, ivec)));
}

QFileInfo const& Datafile::fileInfo() const {
    return fileInfo_;
}

str Datafile::fileName() const {
    return fileInfo_.fileName();
}

QSharedPointer<Image> Datafile::foldedImage() const {
    debug::ensure(!datasequence_.isEmpty());
    QSharedPointer<Image> ret(new Image(datasequence_.first()->imageSize()));
    for (auto& one : datasequence_)
        ret->addIntens(*one->image());
    return ret;
}
