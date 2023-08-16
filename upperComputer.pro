
QT       += core gui
QT       += core gui serialport
QT       += serialport
QT       += charts
QT       += core gui network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    matlabthread.cpp \
    serialport.cpp \
    tcpsocket.cpp

HEADERS += \
    lidarHandle.h \
    lidarHandle.h \
    mainwindow.h \
    matlabthread.h \
    mclcppclass.h \
    serialport.h \
    tcpsocket.h \
    test.h

FORMS += \
    mainwindow.ui \
    serialport.ui \
    tcpsocket.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


DEFINES += __MW_STDINT_H__

INCLUDEPATH += D:/Tools/matlab/extern/include
INCLUDEPATH += D:/Tools/matlab/extern/include/win64
LIBS += -LD:/Tools/matlab/extern/lib/win64/microsoft -llibmex
LIBS += -LD:/Tools/matlab/extern/lib/win64/microsoft -llibmx
LIBS += -LD:/Tools/matlab/extern/lib/win64/microsoft -llibmat
LIBS += -LD:/Tools/matlab/extern/lib/win64/microsoft -llibeng
LIBS += -LD:/Tools/matlab/extern/lib/win64/microsoft -lmclmcr
LIBS += -LD:/Tools/matlab/extern/lib/win64/microsoft -lmclmcrrt

win32: LIBS += -L$$PWD/./ -llidarHandle

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
