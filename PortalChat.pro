QT += qml quick widgets network webview

CONFIG += c++11

SOURCES += main.cpp \
    profiles.cpp \
    jobs.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

HEADERS += \
    profiles.h \
    jobs.h

DISTFILES +=
