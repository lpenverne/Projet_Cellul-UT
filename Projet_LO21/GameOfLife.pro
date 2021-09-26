QT += widgets
QT += testlib
CONFIG += c++11
SOURCES += \
    automatePerso.cpp \
    main.cpp \
    menu.cpp

HEADERS += \
    automatePerso.h \
    menu.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

