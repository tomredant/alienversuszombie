#include "settings.h"
#include "ui_settings.h"
#include "gameproperties.h"
Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setWindowFlags(Qt::Drawer);

    ui->setupUi(this);

    //ui->sliderZombieFrequency
    //ui->sliderZombieSpeed
    //ui->comboAlienLife

    ui->comboAlienLife->addItem("1", 1);
    ui->comboAlienLife->addItem("2", 2);
    ui->comboAlienLife->addItem("5", 5);
    ui->comboAlienLife->addItem("10", 10);
    ui->comboAlienLife->addItem("20", 20);
    ui->comboAlienLife->setCurrentIndex(2);
    ui->lineEditCharacters->setText(ALLOWED_CHARACTERS);



}

Settings::~Settings()
{
    delete ui;
}
