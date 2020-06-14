TEMPLATE = app
QT += quick
QT += qml quick widgets
#CONFIG += c++11 thread
CONFIG += console c++11 thread
CONFIG -= app_bundle
#CONFIG -= qt

LIBS +=/usr/lib/libboost_thread.a

include(json/json.pri)

SOURCES += \
        FC_BuddyItem.cpp \
        FC_BuddyModel.cpp \
        FC_BuddyTeam.cpp \
        fc_buddylist_ctrl.cpp \
        fc_client.cpp \
        fc_connection.cpp \
        fc_display.cpp \
        fc_instance_handle.cpp \
        fc_message.cpp \
        fc_message_handle.cpp \
        fc_message_instance.cpp \
        fc_message_listmodel.cpp \
        fc_profile.cpp \
        fc_profile_handle.cpp \
        fc_thread_pool.cpp \
        main.cpp

HEADERS += \
    FC_BuddyItem.h \
    FC_BuddyModel.h \
    FC_BuddyTeam.h \
    fc_buddylist_ctrl.h \
    fc_client.h \
    fc_connection.h \
    fc_display.h \
    fc_header.h \
    fc_instance_handle.h \
    fc_message.h \
    fc_message_handle.h \
    fc_message_instance.h \
    fc_message_listmodel.h \
    fc_profile.h \
    fc_profile_handle.h \
    fc_thread_pool.h



RESOURCES += \
    qml.qrc \

