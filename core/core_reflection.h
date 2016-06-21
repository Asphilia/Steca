// ************************************************************************** //
//
//  STeCa2:    StressTextureCalculator ver. 2
//
//! @file      core_reflection.h
//! @brief     Reflections
//!
//! @homepage  http://apps.jcns.fz-juelich.de/steca2
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Rebecca Brydon, Jan Burle,  Antti Soininen
//! @authors   Based on the original STeCa by Christian Randau
//
// ************************************************************************** //

#ifndef CORE_REFLECTION_H
#define CORE_REFLECTION_H

#include "core_fit_functions.h"
#include "types/core_types_fwd.h"
#include "types/type_str_lst.h"

namespace core {
//------------------------------------------------------------------------------

class Reflection final {
public:
  static str_lst const& typeStrLst();
  static rcstr          typeTag(ePeakType);

  Reflection(ePeakType = ePeakType::RAW);

  ePeakType type() const;
  void      setType(ePeakType);

  fit::PeakFunction const& peakFunction() const;  // REMOVE

  rcRange range() const;
  void    setRange(rcRange);

  void invalidateGuesses();

  void setGuessPeak(rcXY xy)    { peakFunction_->setGuessedPeak(xy);   }
  void setGuessFWHM(qreal fwhm) { peakFunction_->setGuessedFWHM(fwhm); }

  void fit(rcCurve);

private:
  void setPeakFunction(ePeakType);
  void setPeakFunction(fit::PeakFunction*);

  QScopedPointer<fit::PeakFunction> peakFunction_;

public:
  JsonObj saveJson() const;
  void    loadJson(rcJsonObj) THROWS;
};

//------------------------------------------------------------------------------
}

Q_DECLARE_METATYPE(core::shp_Reflection)

#endif  // CORE_REFLECTION_H
