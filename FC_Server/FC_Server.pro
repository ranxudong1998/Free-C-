TEMPLATE = app
QT += quick
CONFIG += console c++11 thread
CONFIG -= app_bundle
QT += sql
#CONFIG -= qt

#LIBS +=/usr/local/boost_1_72_0/stage/lib/libboost_thread.a
LIBS +=/usr/lib/libboost_thread.a

SOURCES += \
        fc_acceptor.cpp \
        fc_connection.cpp \
        fc_data_base.cpp \
        fc_display.cpp \
        fc_message.cpp \
        fc_message_handle.cpp \
        fc_server.cpp \
        fc_thread_pool.cpp \
        main.cpp

HEADERS += \
    fc_acceptor.h \
    fc_connection.h \
    fc_data_base.h \
    fc_display.h \
    fc_header.h \
    fc_message.h \
    fc_message_handle.h \
    fc_server.h \
    fc_thread_pool.h
