#include "Course_Roll_Pitch.h"
#include "ui_Course_Roll_Pitch.h"

Course_Roll_Pitch::Course_Roll_Pitch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Course_Roll_Pitch)
{
    ui->setupUi(this);
    Course_effect = new QGraphicsColorizeEffect();
    Roll_effect = new QGraphicsColorizeEffect();
    Pitch_effect = new QGraphicsColorizeEffect();

    ui->Course_GW->setScene(new QGraphicsScene(ui->Course_GW));
    Course_Pointer = ui->Course_GW->scene()->addPixmap(QPixmap(":/images/kompass/Course_arrow.jpg"));
    Course_Text = new QGraphicsTextItem;
    Course_Text->setPos(80,25);
    ui->Course_GW->scene()->addItem(Course_Text);
    Course_Pointer->setGraphicsEffect(Course_effect);

    ui->Roll_GW->setScene(new QGraphicsScene(ui->Roll_GW));
    Roll_Pointer = ui->Roll_GW->scene()->addPixmap(QPixmap(":/images/kompass/Roll_arrow.jpg"));
    Roll_Text = new QGraphicsTextItem;
    Roll_Text->setPos(80,25);
    ui->Roll_GW->scene()->addItem(Roll_Text);
    Roll_Pointer->setGraphicsEffect(Roll_effect);

    ui->Pitch_GW->setScene(new QGraphicsScene(ui->Pitch_GW));
    Pitch_Pointer = ui->Pitch_GW->scene()->addPixmap(QPixmap(":/images/kompass/Pitch_arrow.jpg"));
    Pitch_Text = new QGraphicsTextItem;
    Pitch_Text->setPos(0,0);
    ui->Pitch_GW->scene()->addItem(Pitch_Text);
    Pitch_Pointer->setGraphicsEffect(Pitch_effect);

    connect(ui->Course_SB, SIGNAL(valueChanged(double)), this, SLOT(Get_Data()));
    connect(ui->Roll_SB,   SIGNAL(valueChanged(double)), this, SLOT(Get_Data()));
    connect(ui->Pitch_SB,  SIGNAL(valueChanged(double)), this, SLOT(Get_Data()));
}

Course_Roll_Pitch::~Course_Roll_Pitch()
{
    delete ui;
}

void Course_Roll_Pitch::Get_Data()
{
    Course_Pointer->setRotation(ui->Course_SB->value());
    Roll_Pointer  ->setRotation(ui->Roll_SB->value());
    Pitch_Pointer ->setRotation(ui->Pitch_SB->value());

    Course_Text->setPlainText(QString::number(ui->Course_SB->value()));
    Roll_Text->setPlainText(QString::number(ui->Roll_SB->value()));
    Pitch_Text->setPlainText(QString::number(ui->Pitch_SB->value()));

    if(ui->checkBox->isChecked())
    {
        Course_effect->setEnabled(false);
        Roll_effect->setEnabled(false);
        Pitch_effect->setEnabled(false);
    }
    else
    {
        Course_effect->setEnabled(true);
        Roll_effect->setEnabled(true);
        Pitch_effect->setEnabled(true);
    }
}
