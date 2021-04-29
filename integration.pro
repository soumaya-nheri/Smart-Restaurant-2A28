QT       += core gui
QT       += core gui sql
QT       += core gui printsupport
QT       +=multimedia
QT       +=charts
QT       +=serialport
QT       += network
QT       += printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    plat.cpp \
    commande.cpp \
    connection.cpp \
    ajouterres.cpp \
    ajoutertab.cpp \
    client.cpp \
    modifierres.cpp \
    modifiertab.cpp \
    smtp.cpp \
    supprimerres.cpp \
    supprimertab.cpp \
    tables.cpp

HEADERS += \
    mainwindow.h \
    plat.h \
    commande.h \
    connection.h \
    ajouterres.h \
    ajoutertab.h \
    client.h \
    modifierres.h \
    modifiertab.h \
    smtp.h \
    supprimerres.h \
    supprimertab.h \
    tables.h


FORMS += \
    mainwindow.ui \
    ajouterres.ui \
    ajoutertab.ui \
    modifierres.ui \
    modifiertab.ui \
    supprimerres.ui \
    supprimertab.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
