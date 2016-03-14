#ifndef COURSE_ROLL_PITCH_H
#define COURSE_ROLL_PITCH_H

#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsDropShadowEffect>
#include "NMEA_Struct.h"

namespace Ui {
class Course_Roll_Pitch;
}

class Course_Roll_Pitch : public QWidget
{
    Q_OBJECT

public:
    explicit Course_Roll_Pitch(QWidget *parent = 0);
    ~Course_Roll_Pitch();

private:
    Ui::Course_Roll_Pitch *ui;
    QGraphicsPixmapItem     *Course_Pointer, *Roll_Pointer, *Pitch_Pointer;
    QGraphicsTextItem       *Course_Text,    *Roll_Text,    *Pitch_Text;
    QGraphicsColorizeEffect *Course_effect,  *Roll_effect,  *Pitch_effect;
public slots:
    void Get_Data();
};

#endif // COURSE_ROLL_PITCH_H
