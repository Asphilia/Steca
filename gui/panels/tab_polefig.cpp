// ************************************************************************** //
//
//  Steca: stress and texture calculator
//
//! @file      gui/panels/tab_polefig.cpp
//! @brief     Implements class PolefigWidget, and its dependences
//!
//! @homepage  https://github.com/scgmlz/Steca
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016-2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, MAINTAINER)
//
// ************************************************************************** //

#include "tab_polefig.h"
#include "core/session.h"
#include "gui/actions/toggles.h"
#include "gui/actions/triggers.h"
#include <iostream>


// ************************************************************************** //
//  class PolefigWidget
// ************************************************************************** //

PolefigWidget::PolefigWidget()
{
    // initializations
    auto* plot_ = new QWidget; // TODO PlotPolefig; // the main subframe

    // internal connections

    // inbound connection
    connect(gSession, &Session::sigPeaks, [this]() {
            if (isVisible())
                render(); });

    // layout
    auto* buttonBox = new QHBoxLayout;
    buttonBox->addStretch(1);
    buttonBox->addWidget(new XIconButton {&gGui->triggers->exportPolefig});

    auto* controls = new QVBoxLayout;
    //controls->addLayout(selectXY_);
    controls->addStretch(1); // ---
    controls->addLayout(buttonBox);

    auto* layout = new QHBoxLayout;
    layout->addWidget(plot_);
    layout->addLayout(controls);
    layout->setStretch(0,1000);
    setLayout(layout);
}

void PolefigWidget::render()
{
}
