// ************************************************************************** //
//
//  STeCa2:    StressTexCalculator ver. 2
//
//! @file      core_type_geometry.cpp
//!
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Original version: Christian Randau
//! @authors   Version 2: Antti Soininen, Jan Burle, Rebecca Brydon
//
// ************************************************************************** //

#include "core_type_geometry.h"
#include <qmath.h>

namespace core {

//------------------------------------------------------------------------------

qreal const Geometry::MIN_DETECTOR_DISTANCE   = 1000;
qreal const Geometry::MIN_DETECTOR_PIXEL_SIZE = 1;

Geometry::Geometry()
: detectorDistance(MIN_DETECTOR_DISTANCE)
, pixSize(MIN_DETECTOR_PIXEL_SIZE)
, isMidPixOffset(false)
, midPixOffset() {
}

bool Geometry::operator ==(Geometry const& that) const {
  return
    detectorDistance == that.detectorDistance &&
    pixSize          == that.pixSize &&
    isMidPixOffset   == that.isMidPixOffset &&
    midPixOffset     == that.midPixOffset;
}

//------------------------------------------------------------------------------

ImageCut::ImageCut(): ImageCut(0,0,0,0) {
}

ImageCut::ImageCut(uint left_, uint top_, uint right_, uint bottom_)
  : left(left_), top(top_), right(right_), bottom(bottom_) {
}

bool ImageCut::operator ==(const ImageCut &that) const {
  return (left  == that.left  && top    == that.top
       && right == that.right && bottom == that.bottom);
}

QSize ImageCut::marginSize() const {
  return QSize(left+right, top+bottom);
}

//------------------------------------------------------------------------------

Angles::Angles(): Angles(0,0) {
}

Angles::Angles(qreal gamma_, qreal tth_): gamma(gamma_), tth(tth_) {
}

//------------------------------------------------------------------------------

AngleMap::AngleMap() {
}

void AngleMap::calculate(qreal midTth, Geometry const& geometry,
                         QSize const& size, ImageCut const& cut, rcIJ midPix) {
  arrAngles_.fill(size);
  rgeGamma_.invalidate(); rgeTth_.invalidate();

  if (size.isEmpty()) return;

  midTth = deg2rad(midTth);
  qreal pixSize = geometry.pixSize, detDist = geometry.detectorDistance;

  for_int (i, size.width()) {
    qreal x = (i - midPix.i) * pixSize;
    qreal tthHorz = midTth + atan(x / detDist);
    qreal h = cos(tthHorz) * hypot(x, detDist);

    for_int (j, size.height()) {
      qreal y = - (j - midPix.j) * pixSize;
      qreal z = hypot(x,y);
      qreal pixDetDist = hypot(z, detDist);
      qreal tth = acos(h / pixDetDist);

      qreal r = sqrt((pixDetDist * pixDetDist) - (h * h));
      qreal gamma = asin(y / r);

      if (tthHorz < 0) {
        tth   = -tth;
        gamma = -gamma;
      }

      arrAngles_.setAt(i,j,Angles(rad2deg(gamma),rad2deg(tth)));
    }
  }

  for (int i = cut.left, iEnd = size.width() - cut.right; i < iEnd; ++i) {
    for (int j = cut.top, jEnd = size.height() - cut.bottom; j < jEnd; ++j) {
      auto &as = arrAngles_.at(i,j);
      rgeGamma_.extendBy(as.gamma);
      rgeTth_.extendBy(as.tth);
    }
  }
}

//------------------------------------------------------------------------------
}
// eof