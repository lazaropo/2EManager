QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

QMAKE_CXXFLAGS += -std=c++17
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    combatantwidget.cpp

HEADERS += \
    ../Model/SubjectBase.h \
    ../Model/SimpleEffect.h \
    ../Model/Controller.h \
    ../Model/SimpleEffectBuilder.h \
    ../Model/Combatant.h \
    ../Model/CommandBase.h \
    ../Model/CommandsImplementation/HealCommand.h \
    ../Model/CommandsImplementation/HarmCommand.h \
    ../Model/CommandsImplementation.h \
    ../Model/EffectDirector.h \
    ../Model/EffectExecutor.h \
    ../Model/Mediator.h \
    ../Model/Model.h \
    combatantwidget.h

FORMS += \
    combatantwidget.ui

TRANSLATIONS += \
    CombatantWidget_ru_RU.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
