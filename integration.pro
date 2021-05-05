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
    conge.cpp \
    database.cpp \
    evenement.cpp \
    home.cpp \
    main.cpp \
    mainwindow.cpp \
    mainwindow0.cpp \
    offre.cpp \
    planning.cpp \
    plat.cpp \
    commande.cpp \
    connection.cpp \
    ajouterres.cpp \
    ajoutertab.cpp \
    client.cpp \
    modifierres.cpp \
    modifiertab.cpp \
    smtp.cpp \
    staff.cpp \
    supprimerres.cpp \
    supprimertab.cpp \
    tables.cpp

HEADERS += \
    conge.h \
    database.h \
    evenement.h \
    home.h \
    mainwindow.h \
    mainwindow0.h \
    offre.h \
    planning.h \
    plat.h \
    commande.h \
    connection.h \
    ajouterres.h \
    ajoutertab.h \
    client.h \
    modifierres.h \
    modifiertab.h \
    querDefines.h \
    smtp.h \
    staff.h \
    supprimerres.h \
    supprimertab.h \
    tables.h


FORMS += \
    mainwindow.ui \
    ajouterres.ui \
    ajoutertab.ui \
    mainwindow0.ui \
    modifierres.ui \
    modifiertab.ui \
    supprimerres.ui \
    supprimertab.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    BD.sql \
    Click.wav \
    SyNet.qss \
    integration.pro.user \
    integration.pro.user.bd35519 \
    music.mp3 \
    style.qss

RESOURCES += \
    ressources.qrc
