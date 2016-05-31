// ************************************************************************** //
//
//  STeCa2:    StressTexCalculator ver. 2
//
//! @file      output_diffractograms.h
//! @brief     Output of Diffractograms.
//!
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Original version: Christian Randau
//! @authors   Version 2: Antti Soininen, Jan Burle, Rebecca Brydon
//
// ************************************************************************** //

#ifndef OUTPUT_DIFFRACTOGRAMS_H
#define OUTPUT_DIFFRACTOGRAMS_H

#include "output_dialogs.h"

namespace gui { namespace output {
//------------------------------------------------------------------------------

class DiffractogramsParams : public Params {
  SUPER(DiffractogramsParams, Params)
public:
  DiffractogramsParams(TheHub&);
};

//------------------------------------------------------------------------------

class TabDiffractogramsSave : public TabSave {
  SUPER(TabDiffractogramsSave, TabSave)
public:
  TabDiffractogramsSave(TheHub&, Params&);

protected:
  QRadioButton *rbCurrent_, *rbAllSequential_, *rbAll_;
};

//------------------------------------------------------------------------------

class DiffractogramsFrame : public Frame {
  SUPER(DiffractogramsFrame, Frame)
public:
  DiffractogramsFrame(TheHub&, rcstr title, QWidget*);

protected:
  TabDiffractogramsSave *tabSave_;

  void outputCurves(core::rcRange rgeGamma, qreal gammaStep, core::rcDataset dataset);
  void outputCurve(core::rcDataset dataset);

  void outputCurrDiffractogram();
  void outputAllDiffractograms();
};

//------------------------------------------------------------------------------
}}
#endif  // OUTPUT_Diffractograms_H
