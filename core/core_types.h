// ************************************************************************** //
//
//  STeCa2:    StressTexCalculator ver. 2
//
//! @file      core_types.h
//! @brief     Commonly uses types.
//!
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Original version: Christian Randau
//! @authors   Version 2: Antti Soininen, Jan Burle, Rebecca Brydon
//
// ************************************************************************** //

#include "core_defs.h"

#ifndef CORE_TYPES_H
#define CORE_TYPES_H

class QJsonObject;

namespace core {
//------------------------------------------------------------------------------
// for saving / loading the session file

typedef QJsonObject   JsonObj;
typedef JsonObj       &rJsonObj;
typedef JsonObj const &rcJsonObj;

// load / save helpers

qreal loadRealFrom(rcJsonObj, rcstr tag) THROWS;
void  saveRealTo(rJsonObj,  rcstr tag, qreal);

//------------------------------------------------------------------------------
// typedefs

typedef float intens_t;   ///< short for intensity. float should suffice

class Lens;       typedef QSharedPointer<Lens>        shp_LensSystem; // RENAME to shp_LensSystem
class File;       typedef QSharedPointer<File>        shp_File;
class Dataset;    typedef QSharedPointer<Dataset>     shp_Dataset;
class Reflection; typedef QSharedPointer<Reflection>  shp_Reflection;

//------------------------------------------------------------------------------
// conversions

qreal deg_rad(qreal rad);   ///< conversion: degrees <= radians
qreal rad_deg(qreal deg);   ///< conversion: radians <= degrees

//------------------------------------------------------------------------------
/// 2D point

struct XY {
  XY();
  XY(qreal, qreal);

  qreal x, y;

  bool isDefined() const;

  void loadFrom(rcJsonObj) THROWS;
  void saveTo(rJsonObj) const;
};

//------------------------------------------------------------------------------
/// Diffraction angles pair

struct DiffractionAngles {
  DiffractionAngles(qreal gamma = 0, qreal tth = 0);

  qreal gamma, tth;
};

//------------------------------------------------------------------------------
/// range of values as a closed interval

struct Range {
  Range();                        ///< invalid (NaN)
  Range(qreal val);               ///< singular, min == max
  Range(qreal min, qreal max);    ///< normal

  static Range infinite();        ///< factory: -inf .. +inf

  void  invalidate();             ///< make invalid
  bool  isValid() const;          ///< is not NaN

  qreal width()  const;
  qreal center() const;

  qreal min, max;                 ///< this is the range

  void  set(qreal val);           ///< make singular
  void  set(qreal min,qreal max); ///< must be: min <= max
  void  safeSet(qreal,qreal);     ///< will be set in the right order min/max

  static Range safeFrom(qreal,qreal); ///< safe factory

  void  extend(qreal);            ///< extend to include the number
  void  extend(Range const&);     ///< extend to include the range

  // these may be called only on valid intervals
  bool  contains(qreal val)      const;
  bool  contains(Range const&)   const;
  bool  intersects(Range const&) const;

  /// limit the number to the interval, as qBound woul
  qreal bound(qreal)             const;

  void loadFrom(rcJsonObj);
  void saveTo(rJsonObj) const;
};

//------------------------------------------------------------------------------
/// A set of *sorted* non-overlapping ranges

class Ranges {
public:
  Ranges();

  void clear();
  bool isEmpty()          const;
  uint count()            const;

  Range const& at(uint i) const;

  /// collapses overlapping ranges to one; returns whether there was a change
  bool add(Range const&);
  /// removes (cuts out) a range; returns whether there was a change
  bool rem(Range const&);

private:
  void sort();
  QVector<Range> ranges;

public:
  void loadFrom(rcJsonObj);
  void saveTo(rJsonObj) const;
};

//------------------------------------------------------------------------------
}

#endif // CORE_TYPES_H
