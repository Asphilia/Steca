// ************************************************************************** //
//
//  Steca: stress and texture calculator
//
//! @file      gui/output/output_diffractograms.h
//! @brief     Defines class DiffractogramsFrame
//!
//! @homepage  https://github.com/scgmlz/Steca
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016-2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, MAINTAINER)
//
// ************************************************************************** //

#ifndef OUTPUT_DIFFRACTOGRAMS_H
#define OUTPUT_DIFFRACTOGRAMS_H

#include "frame.h"

class OutputData;

//! The modal dialog for saving diffractograms
class DiffractogramsFrame final : public Frame {
public:
    DiffractogramsFrame(rcstr title, QWidget*);

private:
    class TabDiffractogramsSave* tabSave_;

    vec<vec<OutputData>> outputAllDiffractograms();

    void saveDiffractogramOutput();
    void writeCurrDiffractogramToFile(rcstr filePath, rcstr separator);
    void writeAllDiffractogramsToFiles(rcstr filePath, rcstr separator, bool oneFile);
};

#endif // OUTPUT_DIFFRACTOGRAMS_H
