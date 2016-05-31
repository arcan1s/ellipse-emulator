CONFIG += qt
win32: CONFIG += static

# libraries
QT += gui widgets
win32: LIBS += -L/usr/i686-w64-mingw32/lib/qt/plugins/platforms/ -lqwindows -L/usr/i686-w64-mingw32/lib/ -lQt5PlatformSupport
INCLUDEPATH += ../

# sources
HEADERS += ellipseemulator.h
SOURCES += ellipseemulator.cpp main.cpp
FORMS += ellipseemulator.ui
