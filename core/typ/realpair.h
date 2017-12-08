// ************************************************************************** //
//
//  Steca2: stress and texture calculator
//
//! @file      core/typ/realpair.h
//! @brief     Defines class qpair
//!
//! @homepage  https://github.com/scgmlz/Steca2
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ (see CITATION, MAINTAINER)
//
// ************************************************************************** //

#ifndef REALPAIR_H
#define REALPAIR_H

#include "def/comparable.h"
#include "def/exception.h"
#include "def/macros.h"

namespace typ {
class JsonObj;
}

//! 2D point, reals
class qpair {
    public:

    qreal x, y;

    qpair() { invalidate(); }
    qpair(qreal x_, qreal y_) : x(x_), y(y_) {}

    COMPARABLE(qpair const&);

    void invalidate(); // x,y <- NAN
    bool isValid() const { return !qIsNaN(x) && !qIsNaN(y); }

    typ::JsonObj saveJson() const;
    void loadJson(typ::JsonObj const&) THROWS;
};

#endif // REALPAIR_H
