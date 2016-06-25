// ************************************************************************** //
//
//  STeCa2:    StressTextureCalculator ver. 2
//
//! @file      typ_angles.cpp
//!
//! @homepage  http://apps.jcns.fz-juelich.de/steca2
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Rebecca Brydon, Jan Burle,  Antti Soininen
//! @authors   Based on the original STeCa by Christian Randau
//
// ************************************************************************** //

#include "typ_angles.h"
#include <qmath.h>

namespace typ {
//------------------------------------------------------------------------------

deg::deg(rad r) {
  val_ = r.toDeg();
}

rad deg::toRad() const {
  return val_ * (M_PI / 180);
}

deg& deg::operator+=(deg const& that) {
  val_ += that.val_;
  return *this;
}

deg& deg::operator*=(deg const& that) {
  val_ *= that.val_;
  return *this;
}

deg deg::normalized() {
  static qreal const MAX = 360;
  qreal norm = fmod(val_, MAX);
  if (norm < 0) norm += MAX;
  return norm;
}

//------------------------------------------------------------------------------

rad::rad(deg d) {
  val_ = d.toRad();
}

deg rad::toDeg() const {
  return val_ * (180 / M_PI);
}

rad& rad::operator+=(rad const& that) {
  val_ += that.val_;
  return *this;
}

rad& rad::operator*=(rad const& that) {
  val_ *= that.val_;
  return *this;
}

//------------------------------------------------------------------------------
}
// eof
