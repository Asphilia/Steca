//  ***********************************************************************************************
//
//  Steca: stress and texture calculator
//
//! @file      gui/view/plot_polefig.cpp
//! @brief     Implements class PlotPolefig
//!
//! @homepage  https://github.com/scgmlz/Steca
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016-2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, MAINTAINER)
//
//  ***********************************************************************************************

#include "gui/view/plot_polefig.h"
#include "core/session.h"
#include "qcr/base/debug.h"

namespace {

const double alphaMAX {90};

//! Color map for polefigure: shades of blue.
QColor intenGraph(double inten, double maxInten) {
    if (!qIsFinite(inten) || qIsNaN(maxInten) || maxInten <= 0)
        return { qRgb(0x00, 0x00, 0x00) };

    inten /= maxInten;

    return { qRgb(0, 0, int(0xff * (1 - inten / 3))) };
}

} //namespace


PlotPolefig::PlotPolefig()
{
    setRemake ([this](){
            peakInfos_ = gSession->allPeaks.curentPeakInfos();
            QWidget::update(); // Which then calls paintEvent. Only so we can use QPainter.
        });
}

//! Plots the figure, using cached data points (which are computed by remake()).
void PlotPolefig::paintEvent(QPaintEvent*)
{
    qDebug() << "PlotPolefig::refresh()1";

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    int w = size().width(), h = size().height();
    painter.translate(w / 2, h / 2);

    p_ = &painter;
    r_ = qMin(w, h) / 2;

    paintGrid();

    if (peakInfos_)
        paintPoints();
    qDebug() << "PlotPolefig::refresh()9";
}

void PlotPolefig::paintGrid()
{
    QPen penMajor(Qt::gray), penMinor(Qt::lightGray);
    QPointF centre(0, 0);

    for (int alpha = 10; alpha <= 90; alpha += 10) {
        double r = r_ / alphaMAX * alpha;
        p_->setPen(!(alpha % 30) ? penMajor : penMinor);
        circle(centre, r);
    }

    for (int beta = 0; beta < 360; beta += 10) {
        p_->setPen(!(beta % 30) ? penMajor : penMinor);
        p_->drawLine(p(10, beta), p(90, beta));
    }

    QPen penMark(Qt::darkGreen);
    p_->setPen(penMark);
    double avgAlphaMax = gSession->params.interpolParams.avgAlphaMax.val();
    circle(centre, r_ * avgAlphaMax / alphaMAX);
}

void PlotPolefig::paintPoints()
{
    double rgeMax = 0;
    ASSERT(peakInfos_);
    for (const PeakInfo& r : peakInfos_->peaks())
        rgeMax = std::max(rgeMax, r.inten());

    /*
[Jan:] As I read the code: the body of the 'for' loop (for all points) is guarded by
'if (qIsFinite(inten))'. NaNs are not finite, so they do not get painted.

Inside the outer 'if' (for finite inten) is 'if (flat) ... else' where the 'then'
branch paints all points blue and the same size (.5), and the 'else' branch paints
them in various colours and size according to intensity.

The 'flat' flag is controlled by the check box that is in the corner of the pole graph.

NaNs (intensities) do not occur in computed points, only in interpolated points,
when interpolation fails.
    */
    for (const PeakInfo& r : peakInfos_->peaks()) {
        double inten = r.inten();
        if (!qIsFinite(inten)) // nan comes from interpolation
            continue;
        const QPointF& pp = p(r.alpha(), r.beta());
        if (flat.val()) {
            QColor color(Qt::blue);
            p_->setPen(color);
            p_->setBrush(color);
            circle(pp, .5);
        } else {
            inten /= rgeMax;
            QColor color = intenGraph(inten, 1);
            p_->setPen(color);
            p_->setBrush(color);
            circle(pp, inten * r_ / 60); // TODO scale to max inten
        }
    }
}

//! Point in floating-point precision
QPointF PlotPolefig::p(deg alpha, deg beta) const
{
    double r = r_ * alpha / alphaMAX;
    rad betaRad = beta.toRad();
    return QPointF(r * cos(betaRad), -r * sin(betaRad));
}

void PlotPolefig::circle(QPointF c, double r)
{
    p_->drawEllipse(c, r, r);
}
