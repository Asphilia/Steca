//  ***********************************************************************************************
//
//  libqcr: capture and replay Qt widget actions
//
//! @file      qcr/widgets/views.cpp
//! @brief     Implements enhanced view widgets QcrIcon, QcrLineDisplay
//!
//! @homepage  https://github.com/scgmlz/Steca
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018-
//! @author    Joachim Wuttke
//
//  ***********************************************************************************************

#include "views.h"
#include "qcr/base/string_ops.h"
#include <QIcon>

QcrIcon::QcrIcon(const QString& fileName)
    : QcrMixin {*this, fileName}
{
    int h = sizeHint().height();
    setPixmap(QIcon(fileName).pixmap(QSize(h, h)));
}

QcrLineDisplay::QcrLineDisplay(const QString& name, std::function<QString()> freshText)
    : QcrMixin {*this, name}
{
    setReadOnly(true);
    setRemake( [this, freshText]() { setText( freshText() ); } );
}

QcrLineDisplay::QcrLineDisplay(const QString& name, int ndigits, bool withDot)
    : QcrLineDisplay {name, []()->QString{return "???";}}
{
    strOp::setWidth(this, ndigits, withDot);
}
