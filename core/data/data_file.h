// ************************************************************************** //
//
//  Steca2: stress and texture calculator
//
//! @file      core/data/data_file.h
//! @brief     Defines ...
//!
//! @homepage  https://github.com/scgmlz/Steca2
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ (see CITATION, MAINTAINER)
//
// ************************************************************************** //

#ifndef DATA_FILE_H
#define DATA_FILE_H

#include <QSharedPointer>

namespace data {

class File;
typedef QSharedPointer<File> shp_File;
}

Q_DECLARE_METATYPE(data::shp_File)

#include "data_dataset.h"
#include <QFileInfo>

namespace data {

//! A file (loaded from a disk file) that contains a number of datasets.
class File final {
    CLASS(File)
public:
    File(rcstr fileName);

    QFileInfo const& fileInfo() const;
    str fileName() const;

    OneDatasets& datasets() { return datasets_; }
    OneDatasets::rc datasets() const { return datasets_; }

private:
    QFileInfo fileInfo_;
    OneDatasets datasets_;
};

} // namespace data

#endif // DATA_FILE_H
