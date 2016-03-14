#ifndef PARSE_NMEA_H
#define PARSE_NMEA_H

#include <QObject>
#include <QString>
#include <QSettings>
#include <QActionEvent>
#include <QMenu>

#include "NMEA_Struct.h"

class Parse_NMEA : public QObject
{
    Q_OBJECT
public:
    explicit Parse_NMEA(QMenu *, QObject *parent = 0);
    ~Parse_NMEA();
    void Make_NMEA(QByteArray &,struct ACCEL &);
signals:

public slots:
    void Parse(const QString &);
    bool Parse_Second_Slot(const QString &);
    void OnOFF_NMEA(QAction*);
private:
    struct NMEA_Data NMEA_Struct;

    QString Text_NMEA;
    QString Text_NMEA_Accel;

    typedef void (Parse_NMEA::*Handler)(QStringList &);

        struct Handle_Struct{
            QString  templ;
            Handler  handler;
        };

    QVector<struct Handle_Struct> Handle_Vector;

    inline double toGrad(const double Grad_Min);

    void rx_first(QStringList &);
    void rx_second(QStringList &);
    void rx_third(QStringList &);

    inline bool Control_Sum(QString &);
};

#endif // PARSE_NMEA_H
