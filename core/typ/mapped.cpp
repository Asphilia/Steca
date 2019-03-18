//  ***********************************************************************************************
//
//  Steca: stress and texture calculator
//
//! @file      core/typ/mapped.h
//! @brief     Implements class Mapped
//!
//! @homepage  https://github.com/scgmlz/Steca
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016-2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, MAINTAINER)
//
//  ***********************************************************************************************

#include "core/typ/mapped.h"
#include "qcr/base/debug.h"

void Mapped::set(const QString& key, double value)
{
    ASSERT(!has(key));
    super::operator[](key) = value;
}

bool Mapped::has(const QString& key) const
{
    return find(key)!=end();
}

double Mapped::doubleAt(const QString& key) const
{
    const QVariant& entry = super::at(key);
    ASSERT(entry.canConvert(QMetaType::Double));
    return entry.value<double>();
}
