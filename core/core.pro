TARGET   = core
TEMPLATE = lib

DEFINES += BUILDING_LIBRARY

CONFIG  += thread rtti exceptions c++11
CONFIG  += silent warn_on

QT      += core

HEADERS += \
    core.h \
    loaders/Caress/car_datatypes.h \
    loaders/Caress/car_globals.h \
    loaders/Caress/raw.h \
    loaders/Caress/ReadData.h \
    defs.h

SOURCES += \
    core.cpp \
    loaders/Caress/raw.cpp \
    loaders/Caress/ReadCaress.cpp \
    defs.cpp

DISTFILES += \
    README \
    loaders/Caress/README
