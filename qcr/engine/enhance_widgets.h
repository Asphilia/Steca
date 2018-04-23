//  ***********************************************************************************************
//
//  libqcr: capture and replay Qt widget actions
//
//! @file      qcr/engine/enhance_widgets.h
//! @brief     Defines classes CSettable, CModal, CModelessDialog
//!
//! @homepage  https://github.com/scgmlz/Steca
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018-
//! @author    Joachim Wuttke
//
//  ***********************************************************************************************

#ifndef ENHANCE_WIDGETS_H
#define ENHANCE_WIDGETS_H

#include <functional> // no auto rm
#include <QDialog>

//! Mix-in for control widgets that can be changed by a console command.
class CSettable {
public:
    virtual void onCommand(const QString&) = 0;
    const QString& name() const { return name_; }
protected:
    CSettable() = delete;
    CSettable(const CSettable&) = delete;
    CSettable(const QString& name);
    ~CSettable();
private:
    const QString name_;
};

//! Base class for all Qcr widgets that hold a single value.
template<class T>
class QcrControl : protected CSettable {
public:
    QcrControl(const QString& name)
        : CSettable(name) {}
    void programaticallySetValue(T val) {
        doSetValue(val);
    }
    virtual T getValue() const = 0;
private:
    virtual void doSetValue(T) = 0;
};

//! Mix-in for modal dialogs.
class CModal {
protected:
    CModal() = delete;
    CModal(const CModal&) = delete;
    CModal(const QString& name);
    ~CModal();
};

//! A modeless dialog with support for capture&replay.
class CModelessDialog : protected QDialog, protected CSettable {
public:
    virtual void onCommand(const QString&);
protected:
    CModelessDialog(QWidget* parent, const QString& name);
private:
    void closeEvent(QCloseEvent*);
};

#endif // ENHANCE_WIDGETS_H
