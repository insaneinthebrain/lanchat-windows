#-------------------------------------------------
#
# Project created by QtCreator 2012-11-13T16:18:43
#
#-------------------------------------------------

    INCLUDEPATH += C:/Qt/qtcreator-2.2.0/minigw/include     #<--Change the include directory to that of your compiler
    LIBS += -LC:/Qt/qtcreator-2.2.0/minigw/lib/ -lws2_32    #<--Change the lib directory to that of your compiler
                                                            #we need these extra lines to link a library that
                                                            #is not normally linked, "libws2_32.a"

QT       += core gui


TARGET = LanChat
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    workthread.cpp

HEADERS  += mainwindow.h \
    workthread.h

FORMS    += mainwindow.ui
