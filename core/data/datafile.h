// ************************************************************************** //
//
//  Steca2: stress and texture calculator
//
//! @file      core/data/datafile.h
//! @brief     Defines class Datafile
//!
//! @homepage  https://github.com/scgmlz/Steca2
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ (see CITATION, MAINTAINER)
//
// ************************************************************************** //

#ifndef DATAFILE_H
#define DATAFILE_H

#include "dataset.h"
#include <QFileInfo>

//! A file (loaded from a disk file) that contains a sequence of datasets.
class Datafile final {
public:
    Datafile(rcstr fileName);
    void addDataset(Metadata const&, typ::size2d const&, inten_vec const&);

    typ::vec<shp_OneDataset> const& datasets() const { return datasets_; }
    typ::size2d imageSize() const { return imageSize_; }

    QFileInfo const& fileInfo() const;
    str fileName() const;
    typ::shp_Image foldedImage() const;

private:
    QFileInfo fileInfo_;
    typ::vec<shp_OneDataset> datasets_;
    typ::size2d imageSize_;
};

typedef QSharedPointer<class Datafile> shp_Datafile;

Q_DECLARE_METATYPE(shp_Datafile)

#endif // DATAFILE_H
