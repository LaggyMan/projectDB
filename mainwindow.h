#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "database.h"
#include "animewindow.h"
#include "ui_mainwindow.h"
#include "registrwindow.h"

#include <QMainWindow>
#include <QVector>
#include <QString>
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
#include <QLineEdit>


namespace Ui {
class MainWindow;
}

// Add this struct definition for AdminAccount
struct AdminAccount {
    QString login;
    QString password;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    DataBase *dbManager;
    QVector<AdminAccount> adminAccounts; // Declare the QVector for admin accounts
    void loadAdminAccounts();
    bool isAdmin(const QString &login, const QString &password);
};

#endif // MAINWINDOW_H
