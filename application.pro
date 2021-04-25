QT       +=sql
QT       += network
QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = smtp
CONFIG += c++11
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ajouter_fournisseur.cpp \
    ajouterproduit.cpp \
    fournisseur.cpp \
    main.cpp \
    mainwindow.cpp \
    modifier_fournisseur.cpp \
    modifierproduit.cpp \
    produit.cpp \
    supprimer_fournisseur.cpp \
    supprimerproduit.cpp

HEADERS += \
    ajouter_fournisseur.h \
    ajouterproduit.h \
    fournisseur.h \
    mainwindow.h \
    modifier_fournisseur.h \
    modifierproduit.h \
    produit.h \
    supprimer_fournisseur.h \
    supprimerproduit.h

FORMS += \
    ajouter_fournisseur.ui \
    ajouterproduit.ui \
    mainwindow.ui \
    modifier_fournisseur.ui \
    modifierproduit.ui \
    supprimer_fournisseur.ui \
    supprimerproduit.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
