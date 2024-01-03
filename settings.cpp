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


    ui->comboAlienLife->addItem("1", 1);
    ui->comboAlienLife->addItem("2", 2);
    ui->comboAlienLife->addItem("5", 5);
    ui->comboAlienLife->addItem("10", 10);
    ui->comboAlienLife->addItem("20", 20);


    ui->comboBullets->addItem("2", 2);
    ui->comboBullets->addItem("4", 4);
    ui->comboBullets->addItem("6", 6);
    ui->comboBullets->addItem("8", 8);
    ui->comboBullets->addItem("10", 10);

    ui->comboBulletsReward->addItem("1", 1);
    ui->comboBulletsReward->addItem("2", 2);
    ui->comboBulletsReward->addItem("4", 4);

    connect(ui->saveButton,SIGNAL(released()), this, SLOT(clickSave()));
    connect(ui->cancelButton,SIGNAL(released()), this, SLOT(clickCancel()));

    applyValuesToGUI();

}


void Settings::applyValuesToGUI() {
    ui->comboAlienLife->setCurrentIndex(2);
    ui->lineEditCharacters->setText(ALLOWED_CHARACTERS);
    ui->sliderZombieSpeed->setValue(ZOMBIE_STEP_SIZE*4);
    ui->sliderZombieFrequency->setValue((int)(1.0f/((double)ZOMBIE_SELDOMNESS)*100));

    for(int i=0;i<ui->comboBullets->count();i++) {
        if(ui->comboBullets->itemData(i) == NUM_BULLETS) {
            ui->comboBullets->setCurrentIndex(i);
            break;
        }
    }

    for(int i=0;i<ui->comboBulletsReward->count();i++) {
        if(ui->comboBulletsReward->itemData(i) == BULLET_REGAIN_AFTER_HIT) {
            ui->comboBulletsReward->setCurrentIndex(i);
            break;
        }
    }

    for(int i=0;i<ui->comboAlienLife->count();i++) {
        if(ui->comboAlienLife->itemData(i) == MAX_NUM_ALIEN_HITS) {
            ui->comboAlienLife->setCurrentIndex(i);
            break;
        }
    }
}


void Settings::clickSave() {
    applyGUIToValues();
    restart();
    hide();
}

void Settings::applyGUIToValues() {
    MAX_NUM_ALIEN_HITS=ui->comboAlienLife->itemData(ui->comboAlienLife->currentIndex()).toInt();
    ALLOWED_CHARACTERS= (ui->lineEditCharacters->text().length() > 0) ? ui->lineEditCharacters->text() : "a";
    ZOMBIE_STEP_SIZE=(int) (((double) ui->sliderZombieSpeed->value())/4);
    ANIMATION_TICK_DECIMATION = 1.0f/ZOMBIE_STEP_SIZE*50;
    ZOMBIE_SELDOMNESS = 100.0f/((double) ui->sliderZombieFrequency->value());
    NUM_BULLETS=ui->comboBullets->itemData(ui->comboBullets->currentIndex()).toInt();
    BULLET_REGAIN_AFTER_HIT=ui->comboBulletsReward->itemData(ui->comboBulletsReward->currentIndex()).toInt();
    applyValuesToGUI();
}

void Settings::clickCancel() {
    applyValuesToGUI();
    hide();
}

Settings::~Settings()
{
    delete ui;
}
