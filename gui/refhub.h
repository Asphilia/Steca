// ************************************************************************** //
//
//  STeCa2:    StressTextureCalculator ver. 2
//
//! @file      refhub.h
//! @brief     Reference to The Hub.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/steca2
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Rebecca Brydon, Jan Burle,  Antti Soininen
//! @authors   Based on the original STeCa by Christian Randau
//
// ************************************************************************** //

#ifndef REFHUB_H
#define REFHUB_H

#include "def/defs.h"
#include "data/data_dataset.h"
#include "data/data_file.h"
#include "calc/calc_reflection.h"
#include <QObject>

namespace gui {
//------------------------------------------------------------------------------
// The base class of the hub that signalls.

class TheHub;

enum class eFittingTab {
  BACKGROUND,
  REFLECTIONS,
};

class TheHubSignallingBase : public QObject {
  SUPER(TheHubSignallingBase, QObject)
  Q_OBJECT
  friend class RefHub;

private:
  TheHub& asHub();

protected:
  // emit signals - only TheHub can call these
  void tellDatasetSelected(data::shp_Dataset);
  void tellSelectedReflection(calc::shp_Reflection);
  void tellReflectionData(calc::shp_Reflection);
  void tellReflectionValues(typ::Range::rc, typ::XY::rc, qreal, bool);

signals:
  void sigFilesChanged();     // the set of loaded files has changed
  void sigFilesSelected();    // the selection of loaded files has changed

  void sigDatasetsChanged();  // the set of datasets collected from selected
                              // files has changed
  void sigDatasetSelected(data::shp_Dataset);

  void sigCorrFile(data::shp_File);
  void sigCorrEnabled(bool);

  void sigReflectionsChanged();
  void sigReflectionSelected(calc::shp_Reflection);
  void sigReflectionData(calc::shp_Reflection);
  void sigReflectionValues(typ::Range const&, typ::XY const&, qreal, bool);

  void sigDisplayChanged();
  void sigGeometryChanged();

  void sigBgChanged();  // ranges and poly: refit
  void sigNormChanged();

  void sigFittingTab(eFittingTab);

protected:
  // to prevent some otherwise recursive calls
  typedef uint level_t;
  level_t sigLevel_ = 0;

  class level_guard {
  public:
    level_guard(level_t&);
   ~level_guard();
  private:
    level_t &level_;
  };
};

//------------------------------------------------------------------------------
// The base class that refers to the hub + support methods.

class RefHub {
public:
  RefHub(TheHub&);

protected:
  TheHub& hub_;

private:
  template <typename Signal, typename Lambda>
  void onHubSignal(Signal signal, Lambda slot) {
    QObject::connect(&hub_, signal, slot);
  }

  // emit signals (through the hub)
protected:
  void tellDatasetSelected(data::shp_Dataset);
  void tellSelectedReflection(calc::shp_Reflection);
  void tellReflectionData(calc::shp_Reflection);
  void tellReflectionValues(typ::Range::rc, typ::XY::rc, qreal, bool);

  // handle same signals
protected:
#define DEFINE_HUB_SIGNAL_HANDLER(name)                      \
  template <typename Lambda> void onSig##name(Lambda slot) { \
    onHubSignal(&TheHubSignallingBase::sig##name, slot);     \
  }

  DEFINE_HUB_SIGNAL_HANDLER(FilesChanged)
  DEFINE_HUB_SIGNAL_HANDLER(FilesSelected)

  DEFINE_HUB_SIGNAL_HANDLER(DatasetsChanged)
  DEFINE_HUB_SIGNAL_HANDLER(DatasetSelected)

  DEFINE_HUB_SIGNAL_HANDLER(CorrFile)
  DEFINE_HUB_SIGNAL_HANDLER(CorrEnabled)

  DEFINE_HUB_SIGNAL_HANDLER(ReflectionsChanged)
  DEFINE_HUB_SIGNAL_HANDLER(ReflectionSelected)
  DEFINE_HUB_SIGNAL_HANDLER(ReflectionData)
  DEFINE_HUB_SIGNAL_HANDLER(ReflectionValues)

  DEFINE_HUB_SIGNAL_HANDLER(DisplayChanged)
  DEFINE_HUB_SIGNAL_HANDLER(GeometryChanged)

  DEFINE_HUB_SIGNAL_HANDLER(BgChanged)
  DEFINE_HUB_SIGNAL_HANDLER(NormChanged)

  DEFINE_HUB_SIGNAL_HANDLER(FittingTab)

#undef DEFINE_HUB_SIGNAL_HANDLER
};

//------------------------------------------------------------------------------
}
#endif // REFHUB_H
