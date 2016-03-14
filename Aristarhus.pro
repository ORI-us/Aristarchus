#-------------------------------------------------
#
# Project created by QtCreator 2013-12-12T09:51:01
#
#-------------------------------------------------

QT       += core gui widgets serialport

TARGET = Aristarhus
TEMPLATE = app

SOURCES += \
    parse_nmea.cpp \
    main.cpp \
    Formulars/Main_Window/settingsdialog.cpp \
    Formulars/Main_Window/mainwindow.cpp \
    Formulars/NMEA_DIALOG/Show_Text.cpp \
    Formulars/NMEA_DIALOG/higlighter.cpp \
    Formulars/NMEA_DIALOG/dialog.cpp \
    Formulars/Course_Roll_Pitch/Course_Roll_Pitch.cpp

HEADERS  += \
    parse_nmea.h \
    Formulars/show_parse.h \
    Formulars/Main_Window/settingsdialog.h \
    Formulars/Main_Window/mainwindow.h \
    Formulars/NMEA_DIALOG/Show_Text.h \
    Formulars/NMEA_DIALOG/higlighter.h \
    Formulars/NMEA_DIALOG/dialog.h \
    NMEA_Struct.h \
    Formulars/Course_Roll_Pitch/Course_Roll_Pitch.h

INCLUDEPATH += ./

RESOURCES += \
    Aristarhus.qrc

FORMS += \
    Formulars/Main_Window/settingsdialog.ui \
    Formulars/Main_Window/mainwindow.ui \
    Formulars/Course_Roll_Pitch/Course_Roll_Pitch.ui

LIBS = -lQt5SerialPort -lm

QMAKE_CXXFLAGS += -Wextra -Wformat=2 -Winit-self -Wstrict-overflow=5 \
                  -Wcast-qual -Wcast-align -Wwrite-strings \
                  -Warray-bounds -Wno-missing-field-initializers \
                  -std=c++11 -pedantic -D_POSIX_C_SOURCE=200809L -Wall
                  
