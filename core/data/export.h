//  ***********************************************************************************************
//
//  Steca: stress and texture calculator
//
//! @file      core/data/export.h
//! @brief     Defines namespace data_export
//!
//! @homepage  https://github.com/scgmlz/Steca
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016-2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, MAINTAINER)
//
//  ***********************************************************************************************

#include <QString>
#include <QTextStream>

class Cluster;
class Curve;
class InfoSequence;
class Range;

namespace data_export {

//! Returns templatedName with '%d' replaced by string representation of num.

//!  The string representation of num has leading zeros, and its number of
//!  digits is determined by the maximum value maxNum.

extern const QStringList defaultFormats;

QString separator(const QString& format);

QString numberedFileName(const QString& templatedName, int num, int maxNum);

void writeCurve(QTextStream& stream, const Curve& curve, const Cluster* cluster,
                const Range& rgeGma, const QString& separator);

void writeInfoSequence(
    QTextStream& stream, const InfoSequence& peakInfos, const QString& separator);

} // namespace data_export
