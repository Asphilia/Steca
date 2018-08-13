//  ***********************************************************************************************
//
//  libqcr: capture and replay Qt widget actions
//
//! @file      qcr/engine/cell.h
//! @brief     Defines and implements class template QcrCell
//!
//! @homepage  https://github.com/scgmlz/Steca
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018-
//! @author    Joachim Wuttke
//
//  ***********************************************************************************************

#ifndef CELL_H
#define CELL_H

//#include "qcr/base/debug.h"
#include "qcr/engine/single_value.h"
#include <functional>

template<class T>
class QcrControl;

//! Holds a single value, and a hook that is executed when the Gui changes the value.
template<class T>
class QcrCell {
public:
    QcrCell(T value) : value_{value} {}
    template<class Q> QcrCell(Q value) = delete; // prevent automatic conversion Q->T
    QcrCell(const QcrCell&) = default;

    void setVal(T);
    void setHook(std::function<void(T&)> hook) { hook_ = hook; }

    T val() const { return value_; }
    //QString name() { return backlink_?backlink_->name():QString("<nameless>"); } // for Debug only

private:
    T value_;
    std::function<void(T&)> hook_ = [](T&){;};
    QcrControl<T>* backlink_ {nullptr};

    friend QcrControl<T>; // may set backlink_, and call guiSetsVal
    void guiSetsVal(T, bool userCall=false);
};

//  ***********************************************************************************************
//  class QcrCell implementation

template<class T>
void QcrCell<T>::setVal(T val)
{
    value_ = val;
    if (backlink_)
        backlink_->programaticallySetValue(val);
}

template<class T>
void QcrCell<T>::guiSetsVal(T val, bool userCall)
{
    value_ = val;
    if (userCall) { // to prevent circular calls; TODO simplify
        hook_(val);
        if (val!=value_) // hook_ may change val; this mechanism is used in RangeControl
            setVal(val);
        Qcr::defaultHook();
    }
}

#endif // CELL_H
