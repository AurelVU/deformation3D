!RENDER {
CONFIG += RENDER
INCLUDEPATH += $$PWD/../

HEADERS += \
    $$PWD/camera.h \
    $$PWD/set3dpoints.h \
    $$PWD/flattable.h

SOURCES += \
    $$PWD/camera.cpp \
    $$PWD/set3dpoints.cpp \
    $$PWD/flattable.cpp

}

HEADERS += \
    $$PWD/model.h \
    $$PWD/scene.h 

SOURCES += \
    $$PWD/model.cpp \
    $$PWD/scene.cpp 
 
