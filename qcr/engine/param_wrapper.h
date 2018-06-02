//  ***********************************************************************************************
//
//  libqcr: capture and replay Qt widget actions
//
//! @file      qcr/engine/param_wrapper.h
//! @brief     Defines and implements templated class ParamWrapper
//!
//! @homepage  https://github.com/scgmlz/Steca
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018-
//! @author    Joachim Wuttke
//
//  ***********************************************************************************************

#ifndef PARAM_WRAPPER_H
#define PARAM_WRAPPER_H

#include "qcr/base/debug.h"
#include <QObject>
#include <functional>
#include <vector>

void remakeAll();

template<class T>
class QcrControl;

//! Holds a single parameter.
template<class T>
class ParamWrapper {
public:
    ParamWrapper() = delete;
    ParamWrapper(T value) : value_{value} {}

    void setVal(T);
    T val() const { return value_; }

    void setPostHook(std::function<void(T)> postHook) { postHook_ = postHook; }
protected:
    T value_;
    std::function<T(T)> coerce_ {[](T val) { return val; }};
    std::function<void(T)> postHook_ = [](T) {};

    friend QcrControl<T>;
    void guiSetsVal(T, bool userCall=false);
    std::function<void(T)> setGuiVal_ = [](T){};
};

//! Holds a single number.
template<class T>
class NumberWrapper : public ParamWrapper<T> {
public:
    NumberWrapper(T value) : ParamWrapper<T>{value} {
        ParamWrapper<T>::coerce_ = [this](T val) { return coerceMinMax(val); }; }
    // NumberWrapper(T value, T _min, T _max) : NumberWrapper<T>{value} { setMin(_min); setMax(_max); }
    void setMinFct(const std::function<T()>& f) { minFct_ = f; hasMin_ = true; }
    void setMaxFct(const std::function<T()>& f) { maxFct_ = f; hasMax_ = true;  }
    void setMin(const T mval) { setMinFct( [mval](){ return mval; } ); }
    void setMax(const T mval) { setMaxFct( [mval](){ return mval; } ); }

private:
    bool hasMin_ {false};
    bool hasMax_ {false};
    const std::function<T()> minFct_ {[]() { return T(); }};
    const std::function<T()> maxFct_ {[]() { return T(); }};
    T coerceMinMax(T val) const;
};

//  ***********************************************************************************************
//  class ParamWrapper implementation

template<class T>
void ParamWrapper<T>::setVal(T val)
{
    T newval = coerce_(val);
    if (newval!=val)
        qDebug() << "Value " << val << " corrected into " << newval;
/*    if (newval==value_) {
        qDebug() << " == " << val << " -> " << newval << " (as before)";
        return;
        }*/
    value_ = newval;
    setGuiVal_(newval);
    // qDebug() << " -> " << val << " -> " << newval <<  " (non-user call)";
}

template<class T>
void ParamWrapper<T>::guiSetsVal(T val, bool userCall)
{
    T newval = coerce_(val);
    if (newval==value_) {
        qDebug() << " == " << val << " (as before)";
        return;
    }
    value_ = newval;
    if (userCall) {
        qDebug() << " -> " << val;
        postHook_(newval);
        remakeAll();
    } else {
        qDebug() << " -> " << val << " (non-user call)";
    }
}

//  ***********************************************************************************************
//  class NumberWrapper implementation

template<class T>
T NumberWrapper<T>::coerceMinMax(T val) const
{
    if (hasMin_)
        val = qMax(val, minFct_());
    if (hasMax_)
        val = qMin(val, maxFct_());
    return val;
}

#endif // PARAM_WRAPPER_H
