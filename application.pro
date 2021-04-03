QT       +=sql
QT       += network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = smtp
CONFIG += c++11
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ajouter.cpp \
    ajouter_2.cpp \
    client.cpp \
    main.cpp \
    mainwindow.cpp \
    modifier.cpp \
    modifier_2.cpp \
    smtp.cpp \
    supprimer.cpp \
    supprimer_2.cpp \
    tables.cpp

HEADERS += \
    ajouter.h \
    ajouter_2.h \
    client.h \
    mainwindow.h \
    modifier.h \
    modifier_2.h \
    smtp.h \
    supprimer.h \
    supprimer_2.h \
    tables.h

FORMS += \
    ajouter.ui \
    ajouter_2.ui \
    mainwindow.ui \
    modifier.ui \
    modifier_2.ui \
    supprimer.ui \
    supprimer_2.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
