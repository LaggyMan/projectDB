#ifndef ANIMEWINDOW_H
#define ANIMEWINDOW_H

#include <QMainWindow>
#include "database.h"
#include "ui_animewindow.h"
#include <QEvent>
#include <QToolTip>
#include <QHelpEvent>
#include <QLabel>
#include <QDialog>
#include "animepage.h"
#include <QStringListModel>
#include <QCompleter>
#include <QMessageBox>

namespace Ui {
class AnimeWindow;
}

class AnimeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AnimeWindow(QWidget *parent = nullptr);
    ~AnimeWindow();

    void receiveDB(DataBase *manager) {
        dbManager = manager;
    }

    void setAsAdmin() {
        isAdmin = true;
    }

    QString getAnimeDescription(const QString &animeName);
    void showAnimeInfoWidget(const QString &animeInfo);
    void hideAnimeInfoWidget();
    void showAnimeInfoOnSelection();
    void onAnimeSelected(const QString &text);

private:
    animepage *animeInfoWidget = nullptr;
    QCompleter *findCompleter;
    Ui::AnimeWindow *ui;
    DataBase *dbManager;
    bool isAdmin = false;
};

#endif // ANIMEWINDOW_H
