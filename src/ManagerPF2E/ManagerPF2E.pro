QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TEMPLATE += SUBDIRS

SUBDIRS += ../EffectDialog/
SUBDIRS += ../CombatantWidget/

SOURCES += \
    main.cpp \
    managerwidget.cpp \
    ../CombatantWidget/combatantwidget.cpp \
    ../CombatantWidget/MyMenuWidget.cpp \
    ../EffectDialog/EffectDialog.cpp

HEADERS += \
    managerwidget.h \
    ../CombatantWidget/combatantwidget.h \
    ../CombatantWidget/MyMenuWidget.h \
    ../EffectDialog/EffectDialog.h

FORMS += \
    managerwidget.ui \
    ../CombatantWidget/combatantwidget.ui \
    ../EffectDialog/effectdialog.ui

TRANSLATIONS += \
    ManagerPF2E_ru_RU.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


