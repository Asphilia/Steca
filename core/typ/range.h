//  ***********************************************************************************************
//
//  Steca: stress and texture calculator
//
//! @file      core/typ/range.h
//! @brief     Defines class Range
//!
//! @homepage  https://github.com/scgmlz/Steca
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016-2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, MAINTAINER)
//
//  ***********************************************************************************************

#ifndef RANGE_H
#define RANGE_H

#include <QJsonArray>
#include <vector> // no auto rm

class JsonObj;

//! a range of values - a closed interval
class Range {
public:
    Range(); //!< invalid (NaN)
    Range(double min, double max);
    Range(const std::vector<double>&);

    static Range safeFrom(double, double); //!< safe factory

    void fromJson(const JsonObj&);
    void invalidate(); //!< make invalid
    void extendBy(double); //!< extend to include the number
    void extendBy(const Range&); //!< extend to include the range
    void set(double min, double max); //!< must be: min <= max
    void setMin(double val);
    void setMax(double val);

    QJsonObject toJson() const;
    bool isValid() const; //!< is not NaN
    bool isEmpty() const; //!< is invalid or empty
    double width() const;
    double center() const;
    Range slice(int i, int n) const;
    bool contains(double) const;
    bool contains(const Range&) const;
    bool intersects(const Range&) const;
    Range intersect(const Range&) const;
    QString to_s(const QString& unit="", int precision=5, int digitsAfter=2) const;

    double min, max; // this is the range
};

#endif // RANGE_H
