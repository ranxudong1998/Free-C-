TEMPLATE = app
QT += quick
QT += qml quick widgets
#CONFIG += c++11 thread
CONFIG += console c++11 thread
CONFIG -= app_bundle
#CONFIG -= qt

LIBS +=/usr/local/include/boost_1_72_0/stage/lib/libboost_thread.a


SOURCES += \
        fc_client.cpp \
        fc_connection.cpp \
        fc_display.cpp \
        fc_message.cpp \
        fc_message_handle.cpp \
        fc_message_instance.cpp \
        fc_message_listmodel.cpp \
        fc_profile.cpp \
        fc_thread_pool.cpp \
        main.cpp

HEADERS += \
    fc_client.h \
    fc_connection.h \
    fc_display.h \
    fc_header.h \
    fc_message.h \
    fc_message_handle.h \
    fc_message_instance.h \
    fc_message_listmodel.h \
    fc_profile.h \
    fc_thread_pool.h



RESOURCES += \
    qml.qrc \

