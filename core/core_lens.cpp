#include "core_lens.h"

#include "core_dataset.h"
#include "types/core_type_angles.h"
#include "types/core_type_image.h"
#include "types/core_type_image_transform.h"

namespace core {
//------------------------------------------------------------------------------

void Lens::nextChangedImpl() {
}

//------------------------------------------------------------------------------

PlainLens::PlainLens(Image const& image, DiffractionAnglesMap const& map)
  :  Lens()
    ,angleMap(&map)
    ,intensityRange(&image.intensRange())
    ,rawImage(&image)
{
}

DiffractionAngles PlainLens::getAngles(uint x, uint y) const {
  return angleMap->at(x, y);
}

uint PlainLens::getPriority() const {
  return Lens::PRIORITY_PLAIN;
}

intens_t PlainLens::getIntensity(uint x, uint y) const {
  return rawImage->at(x, y);
}

Range PlainLens::getIntensityRange() const {
  return *intensityRange;
}

QSize PlainLens::getSize() const {
  return rawImage->size();
}

//------------------------------------------------------------------------------

TransformationLens::TransformationLens(ImageTransform const& transformation)
  :  Lens()
    ,transform(&transformation)
{
}

uint TransformationLens::getPriority() const {
  return Lens::PRIORITY_TRANSFORMATION;
}

DiffractionAngles TransformationLens::getAngles(uint x, uint y) const {
  return next->getAngles(x, y);
}

intens_t TransformationLens::getIntensity(uint x, uint y) const {
  auto s = getSize();
  uint w = s.width();
  uint h = s.height();

  switch (transform->val) {
  case ImageTransform::ROTATE_0:
    break;
  case ImageTransform::ROTATE_1:
    qSwap(x, y);
    y = w - y - 1;
    break;
  case ImageTransform::ROTATE_2:
    x = w - x - 1;
    y = h - y - 1;
    break;
  case ImageTransform::ROTATE_3:
    qSwap(x, y);
    x = h - x - 1;
    break;
  case ImageTransform::MIRROR_ROTATE_0:
    x = w - x - 1;
    break;
  case ImageTransform::MIRROR_ROTATE_1:
    y = h - y - 1;
    qSwap(x, y);
    y = w - y - 1;
    break;
  case ImageTransform::MIRROR_ROTATE_2:
    y = h - y - 1;
    break;
  case ImageTransform::MIRROR_ROTATE_3:
    qSwap(x, y);
    break;
  default:
    NEVER_HERE;
  }

  return next->getIntensity(x, y);
}

Range TransformationLens::getIntensityRange() const {
  return next->getIntensityRange();
}

QSize TransformationLens::getSize() const {
  auto s = next->getSize();
  switch (transform->val) {
  case ImageTransform::ROTATE_0:
  case ImageTransform::ROTATE_2:
  case ImageTransform::MIRROR_ROTATE_0:
  case ImageTransform::MIRROR_ROTATE_2:
    return s;
  case ImageTransform::ROTATE_1:
  case ImageTransform::ROTATE_3:
  case ImageTransform::MIRROR_ROTATE_1:
  case ImageTransform::MIRROR_ROTATE_3:
    s.transpose();
    return s;
  default:
    NEVER_HERE return QSize();
  }
}

//------------------------------------------------------------------------------

ROILens::ROILens(QMargins const& imageMargins): cut(imageMargins) {
}

uint ROILens::getPriority() const {
  return Lens::PRIORITY_ROI;
}

DiffractionAngles ROILens::getAngles(uint x, uint y) const {
  x += cut.left();
  y += cut.top();
  return next->getAngles(x, y);
}

intens_t ROILens::getIntensity(uint x, uint y) const {
  x += cut.left();
  y += cut.top();
  return next->getIntensity(x, y);
}

Range ROILens::getIntensityRange() const {
  return next->getIntensityRange();
}

QSize ROILens::getSize() const {
  auto s = next->getSize();
  s.rwidth()  -= cut.left() + cut.right();
  s.rheight() -= cut.top()  + cut.bottom();
  return s;
}

//------------------------------------------------------------------------------

SensitivityCorrectionLens::SensitivityCorrectionLens(
  Array2D<qreal> const& sensitivityCorrection)
  : correction(&sensitivityCorrection)
{
}

uint SensitivityCorrectionLens::getPriority() const {
  return Lens::PRIORITY_SENSITIVITY_CORRECTION;
}

DiffractionAngles SensitivityCorrectionLens::getAngles(uint x, uint y) const {
  return next->getAngles(x, y);
}

intens_t SensitivityCorrectionLens::getIntensity(uint x, uint y) const {
  const auto in = next->getIntensity(x, y);
  const auto corr = correction->at(x, y);
  return qIsNaN(corr) ? qQNaN() : in * corr;
}

Range SensitivityCorrectionLens::getIntensityRange() const {
  return next->getIntensityRange();
}

QSize SensitivityCorrectionLens::getSize() const {
  return next->getSize();
}

//------------------------------------------------------------------------------

IntensityRangeLens::IntensityRangeLens()
  :  Lens()
    ,range()
{
  nextChangedImpl();
}

uint IntensityRangeLens::getPriority() const {
  return Lens::PRIORITY_INTENSITY_RANGE;
}

DiffractionAngles IntensityRangeLens::getAngles(uint x, uint y) const {
  return next->getAngles(x, y);
}

intens_t IntensityRangeLens::getIntensity(uint x, uint y) const {
  return next->getIntensity(x, y);
}

Range IntensityRangeLens::getIntensityRange() const {
  return range;
}

QSize IntensityRangeLens::getSize() const {
  return next->getSize();
}

void IntensityRangeLens::nextChangedImpl() {
  range.invalidate();
  if (!next) return;

  auto s = getSize();
  for (int iy = 0; iy < s.height(); ++iy) {
    for (int ix = 0; ix < s.width(); ++ix) {
      range.extendBy(getIntensity(ix, iy));
    }
  }
}

//------------------------------------------------------------------------------

GlobalIntensityRangeLens::GlobalIntensityRangeLens(Range const& intensityRange)
  :  Lens()
    ,range(&intensityRange)
{
}

uint GlobalIntensityRangeLens::getPriority() const {
  return Lens::PRIORITY_INTENSITY_RANGE;
}

DiffractionAngles GlobalIntensityRangeLens::getAngles(uint x, uint y) const {
  return next->getAngles(x, y);
}

intens_t GlobalIntensityRangeLens::getIntensity(uint x, uint y) const {
  return next->getIntensity(x, y);
}

Range GlobalIntensityRangeLens::getIntensityRange() const {
  return *range;
}

QSize GlobalIntensityRangeLens::getSize() const {
  return next->getSize();
}
//------------------------------------------------------------------------------

NormalizationLens::NormalizationLens(qreal normVal_) : normVal(normVal_){

}

uint NormalizationLens::getPriority() const {
  return Lens::PRIORITY_NORMALIZATION;
}

DiffractionAngles NormalizationLens::getAngles(uint x, uint y) const {
  return next->getAngles(x,y);
}

intens_t NormalizationLens::getIntensity(uint x, uint y) const {
  return next->getIntensity(x,y)*normVal;
}

Range NormalizationLens::getIntensityRange() const {
  auto range = next->getIntensityRange();
  range.min = range.min * normVal;
  range.max = range.max * normVal;
  return range;
}

QSize NormalizationLens::getSize() const {
  return next->getSize();
}

//------------------------------------------------------------------------------

shp_LensSystem makeLensSystem(Dataset const& dataset,
                              DiffractionAnglesMap const& angleMap) {
    return shp_LensSystem(new PlainLens(dataset.getImage(), angleMap));
}

//------------------------------------------------------------------------------
}

// eof
