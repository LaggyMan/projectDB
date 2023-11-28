#ifndef REGISTRWINDOW_H
#define REGISTRWINDOW_H

#include "database.h"
#include <QDialog>

namespace Ui {
class RegistrWindow;
}

class RegistrWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RegistrWindow(QWidget *parent = nullptr);
    ~RegistrWindow();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::RegistrWindow *ui;
    DataBase *dbManager;
};

#endif // REGISTRWINDOW_H
