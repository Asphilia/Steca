// ************************************************************************** //
//
//  Steca2: stress and texture calculator
//
//! @file      gui/output/output_polefigures.h
//! @brief     Defines class PoleFiguresFrame
//!
//! @homepage  https://github.com/scgmlz/Steca2
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ (see CITATION, MAINTAINER)
//
// ************************************************************************** //

#ifndef OUTPUT_POLEFIGURES_H
#define OUTPUT_POLEFIGURES_H

#include "output_dialogs.h"

namespace gui {
namespace output {

class PoleFiguresFrame : public Frame {
private:
    using super = Frame;
public:
    PoleFiguresFrame(TheHub&, rcstr title, QWidget*);

protected:
    class TabGraph* tabGraph_;
    class TabPoleFiguresSave* tabSave_;

    void displayReflection(uint reflIndex, bool interpolated);

    void savePoleFigureOutput();
    void writePoleFigureOutputFiles(rcstr filePath, uint index);
    void writePoleFile(rcstr filePath, calc::ReflectionInfos, qreal_vec const&);
    void writeListFile(rcstr filePath, calc::ReflectionInfos, qreal_vec const&);
    void writeErrorMask(rcstr filePath, calc::ReflectionInfos, qreal_vec const&);
};

} // namespace output
} // namespace gui

#endif // OUTPUT_POLEFIGURES_H
