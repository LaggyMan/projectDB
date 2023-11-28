#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->password->setEchoMode(QLineEdit::EchoMode::Password);
    QPixmap pix(":/resources/img/Black.jpg");
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowState(Qt::WindowMaximized | Qt::WindowFullScreen);
    ui->img->setFixedSize(this->size());
    ui->img->setPixmap(pix.scaled(this->size(), Qt::KeepAspectRatio));

    dbManager = new DataBase();

    //dbManager->dropUserAccountTable();

    // Предполагаем, что объект db уже создан и подключен к базе данных
//    dbManager->addAnime("Наруто", 2002, "1", "Studio Pierrot", "Описание Наруто");
//    dbManager->addAnime("Ван Пис", 1999, "2", "Toei Animation", "Описание Ван Пис");
//    dbManager->addAnime("Атака титанов", 2013, "3", "Wit Studio", "Описание Атаки титанов");
//    dbManager->addAnime("Токийский гуль", 2014, "4", "Studio Pierrot", "Описание Токийского гуля");
//    dbManager->addAnime("Моя геройская академия", 2016, "5", "Bones", "Описание Моей геройской академии");
//    dbManager->addAnime("Судьба/Ночь схватки", 2006, "6", "ufotable", "Описание Судьбы/Ночи схватки");
//    dbManager->addAnime("Блич", 2004, "7", "Studio Pierrot", "Описание Блича");
//    dbManager->addAnime("Врата Штейна", 2011, "8", "White Fox", "Описание Врат Штейна");
//    dbManager->addAnime("Ковбой Бибоп", 1998, "9", "Sunrise", "Описание Ковбоя Бибопа");
//    dbManager->addAnime("Полный металлический алхимик", 2003, "10", "Bones", "Описание Полного металлического алхимика");

//    dbManager->addAnimeGenre(1, true, false, true, false);  // Наруто: комедия, приключения
//    dbManager->addAnimeGenre(2, true, false, true, false);  // Ван Пис: комедия, приключения
//    dbManager->addAnimeGenre(3, false, true, false, true);  // Атака титанов: драма, ужасы
//    dbManager->addAnimeGenre(4, false, true, false, true);  // Токийский гуль: драма, ужасы
//    dbManager->addAnimeGenre(5, true, true, true, false);   // Моя геройская академия: комедия, драма, приключения
//    dbManager->addAnimeGenre(6, false, true, false, false); // Судьба/Ночь схватки: драма
//    dbManager->addAnimeGenre(7, true, false, false, false); // Блич: комедия
//    dbManager->addAnimeGenre(8, false, true, false, false); // Врата Штейна: драма
//    dbManager->addAnimeGenre(9, true, false, false, false); // Ковбой Бибоп: комедия
//    dbManager->addAnimeGenre(10, true, true, false, false); // Полный металлический алхимик: комедия, драма


//    // Предполагая, что объект db уже создан и подключен к базе данных
//    dbManager->addReview(1, 1, "Отличное аниме!", 9.0, QDate(2021, 1, 1));  // Обзор на "Наруто"
//    dbManager->addReview(2, 2, "Захватывающий сюжет", 8.5, QDate(2021, 2, 1));  // Обзор на "Ван Пис"
//    dbManager->addReview(3, 3, "Невероятный триллер", 9.2, QDate(2021, 3, 2));  // Обзор на "Атака титанов"
//    dbManager->addReview(4, 4, "Глубокий и мрачный", 8.7, QDate(2021, 4, 5));  // Обзор на "Токийский гуль"
//    dbManager->addReview(5, 5, "Полный драйва и энергии", 9.0, QDate(2021, 5, 8));  // Обзор на "Моя геройская академия"
//    dbManager->addReview(6, 6, "Фантастическая графика", 8.8, QDate(2021, 6, 12));  // Обзор на "Судьба/Ночь схватки"
//    dbManager->addReview(7, 7, "Увлекательное приключение", 8.5, QDate(2021, 7, 15));  // Обзор на "Блич"
//    dbManager->addReview(8, 8, "Умный сюжет, отличные персонажи", 9.3, QDate(2021, 8, 20));  // Обзор на "Врата Штейна"
//    dbManager->addReview(9, 9, "Классика жанра", 9.1, QDate(2021, 9, 22));  // Обзор на "Ковбой Бибоп"
//    dbManager->addReview(10, 10, "Превосходное повествование", 9.4, QDate(2021, 10, 25));  // Обзор на "Полный металлический алхимик"

    loadAdminAccounts();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::loadAdminAccounts() {
    QFile file("admin_accounts.json");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Could not open admin_accounts.json");
        return;
    }

    QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll());
    QJsonObject jsonObj = jsonDoc.object();
    QJsonArray adminsArray = jsonObj["admins"].toArray();

    // Store admin accounts in a QVector for easy lookup
    for (const QJsonValue &adminValue : adminsArray) {
        QJsonObject adminObject = adminValue.toObject();
        QString login = adminObject["login"].toString();
        QString password = adminObject["password"].toString();
        adminAccounts.append({login, password});
    }

    file.close();
}

bool MainWindow::isAdmin(const QString &login, const QString &password) {
    // Check if the provided login and password match any admin account
    for (const auto &admin : adminAccounts) {
        if (admin.login == login && admin.password == password) {
            return true;
        }
    }
    return false;
}

void MainWindow::on_pushButton_clicked() {
    // Авторизация
    QString login = ui->login->text();
    QString password = ui->password->text();
    // Проверка на пустые поля
    if (login.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill in all fields");
        return; // Прерываем выполнение функции, если есть пустые поля
    }
    // Проверка, является ли вход администратором
    if (isAdmin(login, password)) {
        // Авторизация успешна и пользователь - админ
        QMessageBox::warning(this, "Error", "You are authorized as an admin");

        // Создаем новое окно AnimeWindow
        AnimeWindow *animeWindow = new AnimeWindow(this);
        animeWindow->setAsAdmin();


        // Закрываем текущее главное окно
        this->close();

        // Показываем новое окно
        animeWindow->showMaximized();

        QSqlTableModel *model = new QSqlTableModel(this, dbManager->getDatabase());
        model->setTable("user_account");
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->select();

        QTableView *view = new QTableView;
        view->setModel(model);
        view->show();

        QSqlQueryModel *modelAnime = new QSqlQueryModel(this);
        modelAnime->setQuery("SELECT * FROM anime", dbManager->getDatabase());
        QTableView *viewAnime = new QTableView;
        viewAnime->setModel(modelAnime);
        viewAnime->show();

        // Для таблицы genres
        QSqlQueryModel *modelGenres = new QSqlQueryModel(this);
        modelGenres->setQuery("SELECT * FROM genres", dbManager->getDatabase());
        QTableView *viewGenres = new QTableView;
        viewGenres->setModel(modelGenres);
        viewGenres->show();

        // Для таблицы review
        QSqlQueryModel *modelReview = new QSqlQueryModel(this);
        modelReview->setQuery("SELECT * FROM review", dbManager->getDatabase());
        QTableView *viewReview = new QTableView;
        viewReview->setModel(modelReview);
        viewReview->show();


    }
    else{
/*
        QSqlQuery query;
        query.prepare("SELECT * FROM users WHERE login = :login AND password = :password");
        query.bindValue(":login", login);
        query.bindValue(":password", password);

        if (query.exec() && query.next()) {
        */
        if (dbManager->checkUser(login, password)) {
            // Check if the logged-in user is an admin
            // Авторизация успешна и пользователь - админ
            QMessageBox::warning(this, "Error", "You are authorized as an user");
            // Создаем новое окно AnimeWindow
            AnimeWindow *animeWindow = new AnimeWindow(this);

            // Закрываем текущее главное окно
            this->close();

            // Показываем новое окно
            animeWindow->showMaximized();

        } else {
            // Ошибка авторизации
            QMessageBox::warning(this, "Error", "Invalid login or password");
        }
    }
}



void MainWindow::on_pushButton_3_clicked()
{
    RegistrWindow *registrWindow = new RegistrWindow(this);
    registrWindow->setWindowModality(Qt::ApplicationModal);

    // Показываем новое окно
    registrWindow->show();
}

