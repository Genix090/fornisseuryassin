QT += core sql
QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

SOURCES += test_oracle.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

