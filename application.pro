QT       +=sql
QT       += network
QT       += printsupport


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = smtp
CONFIG += c++11
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ajouterres.cpp \
    ajoutertab.cpp \
    client.cpp \
    main.cpp \
    mainwindow.cpp \
    mainwindow0.cpp \
    modifierres.cpp \
    modifiertab.cpp \
    smtp.cpp \
    supprimerres.cpp \
    supprimertab.cpp \
    tables.cpp

HEADERS += \
    ajouterres.h \
    ajoutertab.h \
    client.h \
    mainwindow.h \
    mainwindow0.h \
    modifierres.h \
    modifiertab.h \
    smtp.h \
    supprimerres.h \
    supprimertab.h \
    tables.h

FORMS += \
    ajouterres.ui \
    ajoutertab.ui \
    mainwindow.ui \
    mainwindow0.ui \
    modifierres.ui \
    modifiertab.ui \
    supprimerres.ui \
    supprimertab.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
