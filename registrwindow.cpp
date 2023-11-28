#include "registrwindow.h"
#include "ui_registrwindow.h"
#include <QPixmap>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QTableView>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>


RegistrWindow::RegistrWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegistrWindow)
{
    ui->setupUi(this);
}

RegistrWindow::~RegistrWindow()
{
    delete ui;
}


void RegistrWindow::on_pushButton_2_clicked()
{
    // Получение данных для регистрации
    QString username = ui->nameregistr->text().trimmed();
    QString login = ui->loginregistr->text().trimmed();
    QString password = ui->passwordregistr->text().trimmed();

    // Проверка на пустые поля
    if (username.isEmpty() || login.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill in all fields");
        return; // Прерываем выполнение функции, если есть пустые поля
    }

    // Проверка наличия пользователя с таким логином
    if (dbManager->checkUserExistence(login)) {
        QMessageBox::warning(this, "Error", "User with this login already exists");
        return;
    }

    // Попытка регистрации пользователя
    if (dbManager->registerUser(username, login, password)) {
        QMessageBox::information(this, "Success", "Registration successful");
        this->close();
    } else {
        QMessageBox::warning(this, "Error", "Registration failed");
    }
}
