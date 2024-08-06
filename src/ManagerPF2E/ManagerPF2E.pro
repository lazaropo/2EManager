QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

QMAKE_CXXFLAGS += -Wall -Werror -Wextra \
    -pedantic -Wno-unused-parameter \
    -Wno-unused-variable -Wno-delete-non-virtual-dtor #\
#    -fsanitize=address

#QMAKE_LFLAGS += -fsanitize=address

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TEMPLATE += SUBDIRS

SUBDIRS += ../EffectDialog/EffectDialog.pro
SUBDIRS += ../CombatantWidget/CombatantWidget.pro
SUBDIRS += ../CombatantDialog/CombatantDialog.pro
SUBDIRS += ../CommandDialog/CommandDialog.pro

SOURCES += \
    commandicon.cpp \
    dragndropqwidget.cpp \
    dragndropqwidget_commands.cpp \
    main.cpp \
    managerwidget.cpp \
    ../CombatantWidget/combatantwidget.cpp \
    ../CombatantWidget/MyMenuWidget.cpp \
    ../EffectDialog/EffectDialog.cpp \
    ../Model/*.cpp \
    ../Model/CommandsImplementation/*.cpp \
    ../CombatantDialog/combatantdialog.cpp

HEADERS += \
    commandicon.h \
    dragndropqwidget.h \
    dragndropqwidget_commands.h \
    managerwidget.h \    
    ../CombatantWidget/EffectListWidgetItem.h \
    ../CombatantWidget/MyMenuWidget.h \
    ../CombatantWidget/combatantwidget.h \
    ../EffectDialog/EffectDialog.h \
    ../Model/*.h \
    ../Model/CommandsImplementation/*.h \
    ../CombatantDialog/combatantdialog.h

FORMS += \
    managerwidget.ui \
    ../CombatantWidget/combatantwidget.ui \
    ../EffectDialog/effectdialog.ui \
    ../CombatantDialog/combatantdialog.ui

TRANSLATIONS += \
    ManagerPF2E_ru_RU.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc


