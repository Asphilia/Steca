// ************************************************************************** //
//
//  STeCa2:    StressTextureCalculator ver. 2
//
//! @file      core_type_range.h
//! @brief     Range of real values
//!
//! @homepage  http://apps.jcns.fz-juelich.de/steca2
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Rebecca Brydon, Jan Burle,  Antti Soininen
//! @authors   Based on the original STeCa by Christian Randau
//
// ************************************************************************** //

#ifndef CORE_TYPE_RANGE_H
#define CORE_TYPE_RANGE_H

#include "core_defs.h"
#include "core_types_fwd.h"

namespace core {
//------------------------------------------------------------------------------
/// a range of values - a closed interval

struct Range {
  Range();                        ///< invalid (NaN)
  Range(qreal val);               ///< singular, min == max
  Range(qreal min, qreal max);    ///< normal

  static Range infinite();        ///< factory: -inf .. +inf

  void  invalidate();             ///< make invalid
  bool  isValid() const;          ///< is not NaN
  bool  isEmpty() const;          ///< not valid or empty

  qreal width()  const;
  qreal center() const;

  qreal min, max;                 ///< this is the range

  void  set(qreal val);           ///< make singular
  void  set(qreal min,qreal max); ///< must be: min <= max
  void  safeSet(qreal,qreal);     ///< will be set in the right order min/max

  static Range safeFrom(qreal,qreal); ///< safe factory

  void  extendBy(qreal);          ///< extend to include the number
  void  extendBy(rcRange);   ///< extend to include the range

  // these may be called only on valid ranges
  bool  contains(qreal val) const;
  bool  contains(rcRange)   const;
  bool  intersects(rcRange) const;
  Range intersect(rcRange)  const;

  /// limit the number to the interval, as qBound would
  qreal bound(qreal)        const;

  /// divide into slices
  uint  numSlices(qreal& sliceSize /* i/o */) const;

  JsonObj saveJson() const;
  void    loadJson(rcJsonObj) THROWS;
};

//------------------------------------------------------------------------------
/// A set of *sorted* non-overlapping ranges

class Ranges {
public:
  Ranges();

  void clear()             { ranges_.clear();           }

  bool isEmpty()     const { return ranges_.isEmpty();  }
  uint count()       const { return ranges_.count();    }

  rcRange at(uint i) const { return ranges_.at(i);      }

  /// collapses overlapping ranges into one; returns whether there was a change
  bool add(rcRange);
  /// removes (cuts out) a range; returns whether there was a change
  bool rem(rcRange);

private:
  void sort();
  vec<Range> ranges_;

public:
  JsonArr saveJson() const;
  void    loadJson(rcJsonArr) THROWS;
};

//------------------------------------------------------------------------------
}
#endif // CORE_TYPE_RANGE_H
