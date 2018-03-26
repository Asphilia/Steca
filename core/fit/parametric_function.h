// ************************************************************************** //
//
//  Steca: stress and texture calculator
//
//! @file      core/fit/parametric_function.h
//! @brief     Defines class Function
//!
//! @homepage  https://github.com/scgmlz/Steca
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016-2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, MAINTAINER)
//
// ************************************************************************** //

#ifndef PARAMETRIC_FUNCTION_H
#define PARAMETRIC_FUNCTION_H

#include "core/typ/json.h"
#include "core/typ/range.h"

//! Abstract function with parameters

class Function {
public:
    class Parameter final {
    public:
        Parameter();

        double value() const { return value_; }
        double error() const { return error_; }

        Range valueRange() const; // allowed range of values
        void setValueRange(double min, double max);

        void setValue(double value, double error);

        JsonObj toJson() const;
        void fromJson(const JsonObj&) THROWS;

    private:
        double value_, error_;
        Range range_; //!< allowed range of values
    };

    virtual ~Function() {}

    // evaluate the function y = f(x), with given (parValues) or own parameters
    virtual double y(double x, double const* parValues = nullptr) const = 0;

    // partial derivative / parameter, with given (parValues) or own parameters
    virtual double dy(double x, int parIndex, double const* parValues = nullptr) const = 0;

public:
    void setParameterCount(int);
    int parameterCount() const;
    Parameter& parameterAt(int);

    virtual void reset();

    virtual JsonObj toJson() const;
    virtual void fromJson(const JsonObj&) THROWS;
    virtual QString name() const = 0;

protected:
    QVector<Parameter> parameters_;
    double parValue(int parIndex, double const* parValues) const;
    void setValue(int parIndex, double val);
};

#endif // PARAMETRIC_FUNCTION_H
