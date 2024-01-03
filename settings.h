#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>

namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

private:
    Ui::Settings *ui;
    void applyValuesToGUI();
    void applyGUIToValues();

private slots:
    void clickSave();
    void clickCancel();
signals:
    void restart();
};

#endif // SETTINGS_H
