//  ***********************************************************************************************
//
//  Steca: stress and texture calculator
//
//! @file      core/base/angles.h
//! @brief     Defines classes deg and rad.
//!
//! @homepage  https://github.com/scgmlz/Steca
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016-2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, MAINTAINER)
//
//  ***********************************************************************************************

#ifndef ANGLES_H
#define ANGLES_H

#include <QMetaType>

class rad;

//! An angle in degrees
class deg {
public:
    deg(double val = 0) : val_{val} {}
    explicit deg(rad);

    deg& operator+=(const deg&);
    deg& operator*=(double);

    operator double() const { return val_; }
    rad toRad() const;
    deg normalized() const;

private:
    double val_;
};
Q_DECLARE_METATYPE(deg)

//! An angle in radians
class rad {
public:
    rad(double val = 0) : val_{val} {}
    explicit rad(deg);

    operator double() const { return val_; }
    deg toDeg() const;

private:
    double val_;
};

#endif // ANGLES_H
