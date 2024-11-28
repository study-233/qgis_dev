QT       += core gui xml widgets 3dcore 3drender 3dinput 3dextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += ../Desktop_Qt_5_15_2_MSVC2019_64bit-Release/release/qgis_env/Lib/site-packages/numpy/core/include

INCLUDEPATH += ../Desktop_Qt_5_15_2_MSVC2019_64bit-Release/release/qgis_env/include
LIBS += -L../Desktop_Qt_5_15_2_MSVC2019_64bit-Release/release/qgis_env/libs -lpython39

INCLUDEPATH += D:\\OSGeo4W\\apps\\qgis-dev\\include
INCLUDEPATH += D:\\OSGeo4w\\include

LIBS += -L"D:\\OSGeo4W\\apps\\qgis-dev\\lib" -lqgis_app -lqgis_core -lqgis_gui -lqgis_native -lqgis_3d
LIBS += -LD:/OSGeo4W/lib -lgdal_i    # 使用 OSGeo4W 的 libgdal_i.lib
QMAKE_POST_LINK += $$quote(export PROJ_LIB=D:\\OSGeo4W\\share\\proj &&)

SOURCES += \
    changedetectiondockwidget.cpp \
    main.cpp \
    mainwindows.cpp \
    objectdetectiondockwidget.cpp \
    qgis_devlayertreeviewmenuprovider.cpp \
    reconstructiondockwidget.cpp \
    segmentationdockwidget.cpp

HEADERS += \
    PyThreadStateLock.h \
    changedetectiondockwidget.h \
    changedetectionwork.h \
    mainwindows.h \
    objectdetectiondockwidget.h \
    pythonworker.h \
    qgis_devlayertreeviewmenuprovider.h \
    reconstructiondockwidget.h \
    reconstructionwork.h \
    segmentationdockwidget.h

FORMS += \
    changedetectiondockwidget.ui \
    mainwindows.ui \
    objectdetectiondockwidget.ui \
    reconstructiondockwidget.ui \
    segmentationdockwidget.ui

UI_DIR=./UI

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
