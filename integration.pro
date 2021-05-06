QT       += core gui
QT       += core gui sql
QT       += core gui printsupport
QT       +=multimedia
QT       +=charts
QT       +=serialport
QT       += network
QT       += printsupport
QT       += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ajouter_fournisseur.cpp \
    ajouterproduit.cpp \
    conge.cpp \
    database.cpp \
    evenement.cpp \
    fclient.cpp \
    flivraison.cpp \
    fournisseur.cpp \
    home.cpp \
    main.cpp \
    mainwindow.cpp \
    mainwindow0.cpp \
    modifier_fournisseur.cpp \
    modifierproduit.cpp \
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
    produit.cpp \
    smtp.cpp \
    src/emailaddress.cpp \
    src/mimeattachment.cpp \
    src/mimecontentformatter.cpp \
    src/mimefile.cpp \
    src/mimehtml.cpp \
    src/mimeinlinefile.cpp \
    src/mimemessage.cpp \
    src/mimemultipart.cpp \
    src/mimepart.cpp \
    src/mimetext.cpp \
    src/quotedprintable.cpp \
    src/smtpclient.cpp \
    staff.cpp \
    supprimer_fournisseur.cpp \
    supprimerproduit.cpp \
    supprimerres.cpp \
    supprimertab.cpp \
    tables.cpp

HEADERS += \
    ajouter_fournisseur.h \
    ajouterproduit.h \
    conge.h \
    database.h \
    evenement.h \
    fclient.h \
    flivraison.h \
    fournisseur.h \
    home.h \
    mainwindow.h \
    mainwindow0.h \
    modifier_fournisseur.h \
    modifierproduit.h \
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
    produit.h \
    querDefines.h \
    smtp.h \
    src/SmtpMime \
    src/emailaddress.h \
    src/mimeattachment.h \
    src/mimecontentformatter.h \
    src/mimefile.h \
    src/mimehtml.h \
    src/mimeinlinefile.h \
    src/mimemessage.h \
    src/mimemultipart.h \
    src/mimepart.h \
    src/mimetext.h \
    src/quotedprintable.h \
    src/smtpclient.h \
    src/smtpexports.h \
    staff.h \
    supprimer_fournisseur.h \
    supprimerproduit.h \
    supprimerres.h \
    supprimertab.h \
    tables.h


FORMS += \
    ajouter_fournisseur.ui \
    ajouterproduit.ui \
    mainwindow.ui \
    ajouterres.ui \
    ajoutertab.ui \
    mainwindow0.ui \
    modifier_fournisseur.ui \
    modifierproduit.ui \
    modifierres.ui \
    modifiertab.ui \
    supprimer_fournisseur.ui \
    supprimerproduit.ui \
    supprimerres.ui \
    supprimertab.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    BD.sql \
    Click.wav \
    Incrypt.qss \
    SyNet.qss \
    english.qm \
    english.ts \
    francais.ts \
    integration.pro.user \
    integration.pro.user.bd35519 \
    logo.png \
    music.mp3 \
    style.qss

RESOURCES += \
    ressources.qrc \
    ressources.qrc \
    ressources.qrc \
    ressources.qrc \
    traduction.qrc
