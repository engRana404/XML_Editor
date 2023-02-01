QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp\
    Formatting.cpp \
    Xml_Consistency.cpp \
    XML_Minifier.cpp\
    XmlToJson.cpp\
    XmlToTree.cpp\
    XmlGraph.cpp\
    XmlToVector.cpp\
    CorrectErr.cpp\
    Extras.cpp\
    Compression.cpp\


HEADERS += \
    mainwindow.h\
    Xml_Consistency.h\
    XmlToVector.h\
    Formatting.h\
    mainwindow.h\
    XML_Minifier.h\
    XmlToTree.h\
    CorrectErr.h\
    XmlToJson.h\
    Extras.h\
    Compression.h\
    XmlGraph.h\

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
