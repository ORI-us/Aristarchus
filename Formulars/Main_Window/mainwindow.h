
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QtGlobal>
#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QFile>
#include <QDockWidget>
#include <QSettings>

#include <parse_nmea.h>
#include <Formulars/NMEA_DIALOG/dialog.h>
#include <Formulars/New_Dialog/New_Dialog.h>
#include <Formulars/Course_Roll_Pitch/Course_Roll_Pitch.h>

namespace Ui {
class MainWindow;
}

class Console;
class SettingsDialog;
class Panel_Buttons;
class Parse_NMEA;

class MainWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void Show_NMEA_Text(const QByteArray&);
    void Show_BINR_Text(const QByteArray&);
    void Sent_NMEA(QString&);
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void Show_Hide_Slot(bool);
private slots:
    void openSerialPort_1();
    void closeSerialPort_1();
    void openSerialPort_2();
    void closeSerialPort_2();
    void about();
    void write_NMEA_Data_SLOT(const QString &);
    void readDatafromPort_1();
    void readDatafromPort_2();
    void ACCEL_TO_Dialog(const struct POHPR &);
    void handleError(QSerialPort::SerialPortError error);
    void Enable_Connect(bool);
    void Resize_Slot(const QSize &);
    void Language_Change(QAction*);
    void ZDA_Slot(const struct POHPR &);
private:
    void initActionsConnections();
    void NMEA_Select();

    QSettings Settings;
    void ReadSettings();
    void WriteSettings();

    Parse_NMEA *parse_nmea;

    bool BINR_NMEA;
    bool read_Accel;
    Ui::MainWindow *ui;
    Dialog              *dialog;
    New_Dialog          *new_Dialog;
    Course_Roll_Pitch   *CRP;
    SettingsDialog      *settings_1, *settings_2;
    QSerialPort         *serial_1,   *serial_2;
    Parse_NMEA          *parse_NMEA;

    QByteArray          Accel_Byte;

protected:
    void closeEvent(QCloseEvent *);
};

#endif // MAINWINDOW_H
