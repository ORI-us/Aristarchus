#include "parse_nmea.h"
#include <QStringList>
#include <stdio.h>


Parse_NMEA::Parse_NMEA(QMenu *menu, QObject *parent) : QObject(parent)
{
    struct Handle_Struct H_S[] = {
    {"first",  &Parse_NMEA::rx_first},
    {"second", &Parse_NMEA::rx_second},
    {"third",  &Parse_NMEA::rx_third},
     };

    int size_H_S = sizeof(H_S)/sizeof(struct Handle_Struct);

    for(int i = 0; i<size_H_S; i++)
    {
        Handle_Vector.push_back(H_S[i]);
        menu->addAction(H_S[i].templ)->setCheckable(true);
        menu->actions()[i]->setChecked(true);
    }

    connect(menu, SIGNAL(triggered(QAction*)), this, SLOT(OnOFF_NMEA(QAction*)));
}

Parse_NMEA::~Parse_NMEA()
{

}

inline bool Parse_NMEA::Control_Sum(QString &NMEA_Text)
{
        qint8 nmeaCRC = 0;
        int index = NMEA_Text.indexOf('*');

        QString NMEA_Control = NMEA_Text.mid(index+1, index+3);

        bool B = false;
        quint8 Control = (quint8)NMEA_Control.toUInt(&B, 16);

        NMEA_Text = NMEA_Text.mid(0, index);
        NMEA_Text.remove(0,1);

        for (int i = 0; i < NMEA_Text.length(); i++)
        {
            nmeaCRC ^= NMEA_Text.toLocal8Bit()[i];
        }

        if(nmeaCRC == Control)
            return true;
        else
            return false;
}


void Parse_NMEA::Parse(const QString &T_N)
{
    Text_NMEA.push_back(T_N);
    int Size_NMEA = Text_NMEA.size();

    while(Size_NMEA > 0)
    {
        Text_NMEA.remove(0, Text_NMEA.indexOf('$'));

        int index = Text_NMEA.indexOf('*');
        if(index < 0)
            return;

        QString NMEA_Sentence = Text_NMEA.mid(0, index + 3);

        if(Control_Sum(NMEA_Sentence))
        {
            QStringList NMEAList;
            NMEAList << NMEA_Sentence.split(",");

            for(int i = 0; i<Handle_Vector.size(); i++)
            {
                if(Handle_Vector[i].templ == NMEAList[0])
                    (this->*Handle_Vector[i].handler)(NMEAList);
            }
        }
            Text_NMEA.remove(0, index+4);
            if(Text_NMEA[0] == '\r' || Text_NMEA[0] == '\n')
               Text_NMEA.remove(0, 1);

        Size_NMEA = Text_NMEA.size();
    }
}

bool Parse_NMEA::Parse_Second_Slot(const QString &)
{

    return false;
}

inline double Parse_NMEA::toGrad(const double Grad_Min)
{
    unsigned latit = (unsigned)Grad_Min;

    double L = Grad_Min - latit;

    L = L * 5/3;

    L += latit;

    return L;
}


void Parse_NMEA::rx_first(QStringList &)
{

}

void Parse_NMEA::rx_second(QStringList &)
{

}

void Parse_NMEA::rx_third(QStringList &)
{

}

void Parse_NMEA::OnOFF_NMEA(QAction* a)
{
    QString NMEA(a->text());
    if(a->isChecked())
    {
        for(int i = 0; i<Handle_Vector.size(); i++)
        {
            if(Handle_Vector[i].templ == "OFF_" + NMEA)
                Handle_Vector[i].templ = NMEA;
        }
    }
    else
    {
        for(int i = 0; i<Handle_Vector.size(); i++)
        {
            if(Handle_Vector[i].templ == NMEA)
                Handle_Vector[i].templ.push_front("OFF_");
        }
    }

}

void Parse_NMEA::Make_NMEA(QByteArray &Byte, struct ACCEL &)
{
    QString NMEA;

    NMEA += "AHEZ," + QString::number(1)   + ","
                     + QString::number(2) + ","
                     + QString::number(3) + ","
                     + QString::number(4) + ","
                     + QString::number(5) + ","
                     + QString::number(6) + ","
                     + QString::number(7);

    qint8 nmeaCRC = 0;

    for (int i = 0; i < NMEA.length(); i++)
    {
        nmeaCRC ^= NMEA.toLocal8Bit()[i];
    }

    QString B = QString::number(nmeaCRC, 16).toUpper();

    if(B.length()<2)
        B = "0"+B;

    B.resize(2);

    NMEA ="$"+NMEA+"*"+B+"\r\n";

    Byte = NMEA.toLocal8Bit();
}

