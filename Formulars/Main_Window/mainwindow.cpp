#include <QMessageBox>
#include <QtSerialPort/QSerialPort>
#include <QLabel>
#include <QDir>
#include <QTranslator>
#include <QAction>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingsdialog.h"
#include <Formulars/NMEA_DIALOG/dialog.h>
#include <parse_nmea.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), Settings("Aristarhus", "Aristarhus"), BINR_NMEA(0), read_Accel(false),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dialog = new Dialog(Settings);
    setCentralWidget(dialog);
    QAction *dialog_Action = ui->menuView->addAction("Dialog");
    dialog_Action->setCheckable(true);
    dialog_Action->setChecked(true);
    connect(dialog_Action, SIGNAL(triggered(bool)), dialog, SLOT(setVisible(bool)));

    serial_1 = new QSerialPort(this);
    settings_1    = new SettingsDialog(Settings, QString("Port_1"));

    parse_nmea = new Parse_NMEA(ui->menuNMEA);

    CRP = new Course_Roll_Pitch();
    CRP->setWindowTitle("Course Roll Pitch");
    QAction *CHT_Action = ui->menuView->addAction("Course Roll Pitch");
    connect(CHT_Action, SIGNAL(triggered()), CRP, SLOT(show()));

    new_Dialog = new New_Dialog();
    new_Dialog->setWindowTitle("New Dialog");
    QAction *New_dialog_Action = ui->menuView->addAction("New_Dialog");
    connect(New_dialog_Action, SIGNAL(triggered()), new_Dialog, SLOT(show()));

    ui->actionConnect_1->setEnabled(true);
    ui->actionDisconnect_1->setEnabled(false);
    ui->actionQuit->setEnabled(true);
    ui->actionConfigure_1->setEnabled(true);

    initActionsConnections();

    ReadSettings();
}

MainWindow::~MainWindow()
{

}

void MainWindow::closeEvent(QCloseEvent *)
{
    WriteSettings();
    delete(settings_1);
    delete(dialog);
    delete(CRP);
    delete(parse_nmea);
}

void MainWindow::ReadSettings()
{
    Settings.beginGroup("/Windows");
        dialog      ->setHidden(Settings.value("/NMEA_DIalog").toBool());
        CRP         ->setHidden(Settings.value("/CRP").toBool());
    Settings.endGroup();

}

void MainWindow::WriteSettings()
{
    Settings.beginGroup("/Date");
        QString  date(__DATE__);
        date += QString(__TIME__);
        Settings.setValue("Date", date);
    Settings.endGroup();

    Settings.beginGroup("/Windows");
        Settings.setValue("/NMEA_DIalog",   dialog->isHidden());
        Settings.setValue("/CRP",           CRP->isHidden());
    Settings.endGroup();

    Settings.endGroup();
}

void MainWindow::openSerialPort_1()
{
    SettingsDialog::Settings p = settings_1->settings();
    serial_1->setPortName(p.name);
    if (serial_1->open(QIODevice::ReadWrite)) {
        if (serial_1->setBaudRate(p.baudRate)
                && serial_1->setDataBits(p.dataBits)
                && serial_1->setParity(p.parity)
                && serial_1->setStopBits(p.stopBits)
                && serial_1->setFlowControl(p.flowControl)) {

            dialog->setEnabled(true);
            dialog->Read_Button_Settings(false);
            dialog->setLocalEchoEnabled(p.localEchoEnabled);
            ui->actionConnect_1->setEnabled(false);
            ui->actionDisconnect_1->setEnabled(true);
            ui->actionConfigure_1->setEnabled(false);
            ui->statusBar->showMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                                       .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                                       .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));

            dialog->Disable_Enable_Send(true);
        } else {
            serial_1->close();
            QMessageBox::critical(this, tr("Error"), serial_1->errorString());

            ui->statusBar->showMessage(tr("Open error"));
        }
    } else {
        QMessageBox::critical(this, tr("Error"), serial_1->errorString());

        ui->statusBar->showMessage(tr("Configure error"));
    }
}


void MainWindow::closeSerialPort_1()
{
    serial_1->close();
    ui->actionConnect_1->setEnabled(true);
    ui->actionDisconnect_1->setEnabled(false);
    ui->actionConfigure_1->setEnabled(true);
    ui->statusBar->showMessage(tr("Disconnected"));
    dialog->Read_Button_Settings(true);

    dialog->Disable_Enable_Send(false);
}

void MainWindow::about()
{

}

void MainWindow::write_NMEA_Data_SLOT(const QString &str)
{
    BINR_NMEA = 0;
    QByteArray K = str.toLocal8Bit();
    serial_1->write(K);
}

void MainWindow::readDatafromPort_1()
{
    QByteArray data = serial_1->readAll();

    dialog->Show_NMEA_Text(data);
}


void MainWindow::ACCEL_TO_Dialog(const struct POHPR &)
{

}

void MainWindow::Enable_Connect(bool Enable)
{
    ui->actionConnect_1->setEnabled(Enable);
}

void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError)
    {
        closeSerialPort_1();
        QMessageBox::critical(this, tr("Critical Error"), serial_1->errorString());
    }
}

void MainWindow::Show_Hide_Slot(bool enable)
{
    if(enable)
    {
        ReadSettings();
    }
    else
    {
        WriteSettings();
        CRP->hide();
    }
}

void MainWindow::Resize_Slot(const QSize &Size)
{
    QSize S = this->size();
    S.setWidth(S.width() - Size.width());
    this->setSizeIncrement(S);
}


void MainWindow::initActionsConnections()
{
    connect(ui->actionConnect_1,    SIGNAL(triggered()), this,        SLOT(openSerialPort_1()));
    connect(ui->actionDisconnect_1, SIGNAL(triggered()), this,        SLOT(closeSerialPort_1()));
    connect(ui->actionQuit,         SIGNAL(triggered()), this,        SLOT(close()));
    connect(ui->actionConfigure_1,  SIGNAL(triggered()), settings_1,  SLOT(show()));
    connect(ui->actionAbout,        SIGNAL(triggered()), this,        SLOT(about()));
    connect(ui->actionAboutQt,      SIGNAL(triggered()), qApp,        SLOT(aboutQt()));
}
