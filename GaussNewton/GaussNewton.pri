!GAUSSNEWTON_PRI {
CONFIG += GAUSSNEWTON_PRI
INCLUDEPATH += $$PWD/../
include($$PWD/../Eigen/Eigen.pri)

HEADERS += \
    $$PWD/variable.h

SOURCES += \

}

HEADERS += \
    $$PWD/gaussnewton.h

SOURCES += \
    $$PWD/gaussnewton.cpp
