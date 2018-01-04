// ************************************************************************** //
//
//  Steca2: stress and texture calculator
//
//! @file      gui/console.h
//! @brief     Declares class Console
//!
//! @homepage  https://github.com/scgmlz/Steca2
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016-2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, MAINTAINER)
//
// ************************************************************************** //

#ifndef CONSOLE_H
#define CONSOLE_H

#include <QObject>

//! Reads commands from stdin,
class Console : public QObject
{
    Q_OBJECT
public:
    Console();
signals:
    void quit();
private:
    class QSocketNotifier *m_notifier;
private slots:
    void readCommand();
};

#endif // CONSOLE_H
