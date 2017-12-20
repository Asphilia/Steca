// ************************************************************************** //
//
//  Steca2: stress and texture calculator
//
//! @file      gui/settings.h
//! @brief     Defines class Settings
//!
//! @homepage  https://github.com/scgmlz/Steca2
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ (see CITATION, MAINTAINER)
//
// ************************************************************************** //

#ifndef SETTINGS_H
#define SETTINGS_H

#include "actions.h"
#include "def/special_pointers.h"
#include "models.h"
#include "session.h"
#include "typ/exception.h"
#include "typ/range.h"
#include "typ/str.h"
#include <QSettings>

class QSpinBox;
class QDoubleSpinBox;

namespace gui {

class Settings : public QSettings {
private:
    using super = QSettings;
public:
    Settings(rcstr group = "");
    ~Settings();

    QVariant readVariant(rcstr key, QVariant const& def);
    void saveVariant(rcstr key, QVariant const& val) { setValue(key, val); }

    void read(rcstr key, QAction*, bool def = false);
    void save(rcstr key, QAction*);

    void read(rcstr key, QSpinBox*, int def = 0);
    void save(rcstr key, QSpinBox*);

    void read(rcstr key, QDoubleSpinBox*, qreal def = 0);
    void save(rcstr key, QDoubleSpinBox*);

    bool readBool(rcstr key, bool def = false) { return readVariant(key, def).toBool(); }
    void saveBool(rcstr key, bool val) { saveVariant(key, val); }

    int readInt(rcstr key, int def = 0);
    void saveInt(rcstr key, int val) { saveVariant(key, val); }

    qreal readReal(rcstr key, qreal def = 0);
    void saveReal(rcstr key, qreal val) { saveVariant(key, val); }

    str readStr(rcstr key, rcstr def = "") { return readVariant(key, def).toString(); }
    void saveStr(rcstr key, rcstr val) { saveVariant(key, val); }
};

} // namespace gui

#endif // SETTINGS_H