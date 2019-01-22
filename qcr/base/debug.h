//  ***********************************************************************************************
//
//  libqcr: capture and replay Qt widget actions
//
//! @file      qcr/base/debug.h
//! @brief     Includes QtDebug and QtGlobal, and defines preprocessor macro ASSERT
//!
//! @homepage  https://github.com/scgmlz/Steca
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018-
//! @author    Joachim Wuttke
//
//  ***********************************************************************************************

#ifndef DEBUG_H
#define DEBUG_H

#include <QtDebug>
#include <QtGlobal> // protect

#define ASSERT(cond) if (!(cond)) qFatal("assertion failed: " #cond)

#endif // DEBUG_H
