QT += core
QT += gui
QT += opengl

CONFIG += app
CONFIG += console
TARGET = frag_sampler

SOURCES += \
    frag_main.cpp \
    frag_pane.cpp \
    frag_window.cpp \
    frag_window_ut.cpp

OTHER_FILES += \
    shaders/inverse.vert \
    shaders/inverse.frag \
    shaders/median3.vert \
    shaders/median3.frag \
    shaders/mosaic.frag \
    shaders/mosaic.vert \
    shaders/copy.frag \
    shaders/copy.vert

HEADERS += \
    frag_pane.h \
    frag_window.h

FORMS += \
    frag_window.ui

RESOURCES += \
    frag_sampler.qrc

QMAKE_LFLAGS += /INCREMENTAL:NO
