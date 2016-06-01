// ************************************************************************** //
//
//  STeCa2:    StressTexCalculator ver. 2
//
//! @file      core_async.h
//! @brief     Asynchronous computation support.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/steca2
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Antti Soininen, Jan Burle, Rebecca Brydon
//! @authors   Based on the original STeCa by Christian Randau
//
// ************************************************************************** //

#ifndef CORE_ASYNC_H
#define CORE_ASYNC_H

#include "core_defs.h"

class TakesLongTime final {
public:
  TakesLongTime();
 ~TakesLongTime();

  static void (*handler)(bool);
};

class Progress final {
public:
  Progress(uint total, class QProgressBar*);
 ~Progress();

  void setProgress(uint);
  void step();


private:
  uint total_, i_;
  QProgressBar* bar_;
};

#endif  // CORE_ASYNC_H
