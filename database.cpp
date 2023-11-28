#include "database.h"

DataBase::DataBase()
{
    openDatabase();
    createUsersTable();
    createFavoriteAnimeListTable();
    createAnimePageTable();
    createPictureSourceTable();
    createVideoSourceTable();
    createAnimeTable();
    createReviewTable();
    createGenresTable();
}

DataBase::~DataBase()
{
    closeDatabase();
}

bool DataBase::openDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("anime.db");

    if (!db.open()) {
        qDebug() << "Error: Unable to open database";
        return false;
    }

    return true;
}

QSqlDatabase DataBase::getDatabase() const
{
    return db;
}

void DataBase::closeDatabase()
{
    if (db.isOpen()) {
        db.close();
    }
}

bool DataBase::createUsersTable() {
    QSqlQuery createQuery;
    bool success = createQuery.exec(
        "CREATE TABLE IF NOT EXISTS user_account ("
        "user_id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "username TEXT NOT NULL, "
        "login TEXT NOT NULL UNIQUE, "
        "password TEXT NOT NULL, "
        "age INTEGER, "
        "about_me TEXT)"
        );
    return success;
}

/*
bool DataBase::dropUserAccountTable() {
    QSqlQuery query;
    bool success = query.exec("DROP TABLE IF EXISTS `users`");
    if (!success) {
        qDebug() << "Failed to drop User account table:" << query.lastError();
    }
    return success;
}
*/

bool DataBase::createFavoriteAnimeListTable() {
    QSqlQuery query;
    bool success = query.exec(
        "CREATE TABLE IF NOT EXISTS favorite_anime_list ("
        "Anime_id INTEGER,"
        "User_id INTEGER NOT NULL,"
        "PRIMARY KEY (Anime_id),"
        "FOREIGN KEY (User_id) REFERENCES user_account(user_id))" // Внешний ключ
        );
    return success;
}

bool DataBase::createAnimePageTable() {
    QSqlQuery query;
    bool success = query.exec(
        "CREATE TABLE IF NOT EXISTS anime_page ("
        "Anime_id INTEGER NOT NULL,"
        "Picture_ids INTEGER,"
        "Video_ids INTEGER,"
        "Page_id INTEGER,"
        "PRIMARY KEY (Page_id),"
        "FOREIGN KEY (Anime_id) REFERENCES anime(Anime_id))" // Внешний ключ
        );
    return success;
}

bool DataBase::createPictureSourceTable() {
    QSqlQuery query;
    bool success = query.exec(
        "CREATE TABLE IF NOT EXISTS picture_source ("
        "Picture_id INTEGER,"
        "Page_id INTEGER NOT NULL,"
        "Picture_ref VARCHAR(255),"
        "PRIMARY KEY (Picture_id),"
        "FOREIGN KEY (Page_id) REFERENCES anime_page(Page_id))" // Внешний ключ
        );
    return success;
}

bool DataBase::createVideoSourceTable() {
    QSqlQuery query;
    bool success = query.exec(
        "CREATE TABLE IF NOT EXISTS video_source ("
        "Video_id INTEGER,"
        "Page_id INTEGER NOT NULL,"
        "Video_ref VARCHAR(255),"
        "PRIMARY KEY (Video_id),"
        "FOREIGN KEY (Page_id) REFERENCES anime_page(Page_id))" // Внешний ключ
        );
    return success;
}

bool DataBase::createAnimeTable() {
    QSqlQuery query;
    bool success = query.exec(
        "CREATE TABLE IF NOT EXISTS anime ("
        "Anime_id INTEGER,"
        "Name VARCHAR(255),"
        "Year INTEGER,"
        "Genre_id INTEGER NOT NULL,"
        "Studio_name VARCHAR(255),"
        "Description TEXT,"
        "PRIMARY KEY (Anime_id),"
        "FOREIGN KEY (Genre_id) REFERENCES genres(Genre_id))" // Внешний ключ
        );
    return success;
}

bool DataBase::createReviewTable() {
    QSqlQuery query;
    bool success = query.exec(
        "CREATE TABLE IF NOT EXISTS review ("
        "Review_id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "User_id INTEGER NOT NULL,"
        "Anime_id INTEGER NOT NULL,"
        "Comment TEXT,"
        "Rate FLOAT,"
        "Date DATE,"
        "FOREIGN KEY (User_id) REFERENCES user_account(user_id)," // Внешний ключ к user_account
        "FOREIGN KEY (Anime_id) REFERENCES anime(Anime_id))" // Предположим, что есть внешний ключ к таблице anime
        );
    return success;
}


bool DataBase::createGenresTable() {
    QSqlQuery query;
    bool success = query.exec(
        "CREATE TABLE IF NOT EXISTS genres ("
        "Anime_id INTEGER NOT NULL,"
        "Genre_id INTEGER,"
        "Comedy BOOL,"
        "Drama BOOL,"
        "Adventure BOOL,"
        "Horror BOOL,"
        "PRIMARY KEY (Genre_id),"
        "FOREIGN KEY (Anime_id) REFERENCES anime(Anime_id))" // Внешний ключ
        );
    return success;
}

bool DataBase::addAnime(const QString &name, int year, const QString &genreId, const QString &studioName, const QString &description) {
    QSqlQuery query;
    query.prepare("INSERT INTO anime (Name, Year, Genre_id, Studio_name, Description) VALUES (:name, :year, :genreId, :studioName, :description)");
    query.bindValue(":name", name);
    query.bindValue(":year", year);
    query.bindValue(":genreId", genreId);
    query.bindValue(":studioName", studioName);
    query.bindValue(":description", description);

    if (!query.exec()) {
        qDebug() << "Failed to add anime:" << query.lastError();
        return false;
    }
    return true;
}

bool DataBase::addAnimeGenre(int animeId, bool comedy, bool drama, bool adventure, bool horror) {
    QSqlQuery query;
    query.prepare("INSERT INTO genres (Anime_id, Comedy, Drama, Adventure, Horror) VALUES (:animeId, :comedy, :drama, :adventure, :horror)");
    query.bindValue(":animeId", animeId);
    query.bindValue(":comedy", comedy);
    query.bindValue(":drama", drama);
    query.bindValue(":adventure", adventure);
    query.bindValue(":horror", horror);

    if (!query.exec()) {
        qDebug() << "Failed to add anime genre:" << query.lastError();
        return false;
    }
    return true;
}

bool DataBase::addReview(int userId, int animeId, const QString &comment, float rate, const QDate &date) {
    QSqlQuery query;
    query.prepare("INSERT INTO review (User_id, Anime_id, Comment, Rate, Date) VALUES (:userId, :animeId, :comment, :rate, :date)");
    query.bindValue(":userId", userId);
    query.bindValue(":animeId", animeId);
    query.bindValue(":comment", comment);
    query.bindValue(":rate", rate);
    query.bindValue(":date", date.toString("yyyy-MM-dd")); // Формат даты

    if (!query.exec()) {
        qDebug() << "Failed to add review:" << query.lastError();
        return false;
    }
    return true;
}

bool DataBase::insertUser(const QString &username, const QString &login, const QString &password)
{
    QSqlQuery query;
    query.prepare("INSERT INTO user_account (username, login, password) VALUES (:username, :login, :password)");
    query.bindValue(":username", username);
    query.bindValue(":login", login);
    query.bindValue(":password", password);

    return query.exec();
}

bool DataBase::checkUser(const QString &login, const QString &password)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM user_account WHERE login = :login AND password = :password");
    query.bindValue(":login", login);
    query.bindValue(":password", password);

    return query.exec() && query.next();
}

bool DataBase::registerUser(const QString &username, const QString &login, const QString &password)
{
    if (checkUserExistence(login)) {
        // Пользователь с таким логином уже существует
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO user_account (username, login, password) VALUES (:username, :login, :password)");
    query.bindValue(":username", username);
    query.bindValue(":login", login);
    query.bindValue(":password", password);

    return query.exec();
}

QVector<QString> DataBase::getTop3AnimeByRating() {
    QVector<QString> top3Anime;

    QSqlQuery query;
    query.prepare("SELECT anime.Name FROM anime "
                  "INNER JOIN review ON anime.Anime_id = review.Anime_id "
                  "GROUP BY anime.Anime_id "
                  "ORDER BY AVG(review.Rate) DESC "
                  "LIMIT 3");

    if (query.exec()) {
        while (query.next()) {
            QString animeName = query.value(0).toString();
            top3Anime.push_back(animeName);
        }
    } else {
        qDebug() << "Failed to fetch top 3 anime:" << query.lastError();
    }

    return top3Anime;
}

bool DataBase::checkUserExistence(const QString &login)
{
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT * FROM user_account WHERE login = :login");
    checkQuery.bindValue(":login", login);

    return checkQuery.exec() && checkQuery.next();
}
QString DataBase::getAnimeDescriptionByName(const QString &animeName) {
    QString description;

    QSqlQuery query;
    query.prepare("SELECT Description FROM anime WHERE Name = :animeName");
    query.bindValue(":animeName", animeName);

    if (query.exec() && query.next()) {
        description = query.value(0).toString();
    } else {
        qDebug() << "Failed to fetch anime description:" << query.lastError();
    }

    return description;
}
QString DataBase::getGenreNameById(int genreId) {
    QString genreName;

    QSqlQuery query;
    query.prepare("SELECT Genre_id, Comedy, Drama, Adventure, Horror FROM genres WHERE Genre_id = :genreId");
    query.bindValue(":genreId", genreId);

    if (query.exec() && query.next()) {
        bool isComedy = query.value(1).toBool();
        bool isDrama = query.value(2).toBool();
        bool isAdventure = query.value(3).toBool();
        bool isHorror = query.value(4).toBool();

        // Предположим, что ваша база данных имеет определенную логику для идентификации жанров по их ID
        if (isComedy) {
            genreName += "Комедия ";
        } if (isDrama) {
            genreName += "Драма ";
        } if (isAdventure) {
            genreName += "Приключения ";
        } if (isHorror) {
            genreName += "Хоррор ";
        }
        // Добавьте другие жанры, если необходимо
    } else {
        qDebug() << "Failed to fetch genre name:" << query.lastError();
    }

    return genreName;
}

QString DataBase::getAnimeInfo(const QString &animeName) {
    QString animeInfo;

    QSqlQuery query;
    query.prepare("SELECT anime.Name, anime.Year, GROUP_CONCAT(genres.Genre_id), AVG(review.Rate) "
                  "FROM anime "
                  "LEFT JOIN genres ON anime.Anime_id = genres.Anime_id "
                  "LEFT JOIN review ON anime.Anime_id = review.Anime_id "
                  "WHERE anime.Name = :animeName "
                  "GROUP BY anime.Name, anime.Year");

    query.bindValue(":animeName", animeName);

    if (query.exec() && query.next()) {
        QString name = query.value(0).toString();
        int year = query.value(1).toInt();
        QString genreIds = query.value(2).toString();
        qDebug() << genreIds << " ";
        double avgRating = query.value(3).toDouble();

        QStringList genres;
        QStringList genreIdList = genreIds.split(",", QString::SkipEmptyParts);

        // Предположим, что у вас есть метод получения названия жанра по его ID
        for (const QString &genreId : genreIdList) {
            QString genre = getGenreNameById(genreId.toInt());
            genres.append(genre);
        }

        animeInfo = QString("Название: %1,Год выпуска: %2, Жанры: %3, Рейтинг: %4")
            .arg(name)
            .arg(year)
            .arg(genres.join(", "))
            .arg(avgRating);
        qDebug() << animeInfo << " ";
    } else {
        qDebug() << "Failed to fetch anime info:" << query.lastError();
    }

    return animeInfo;
}

QStringList DataBase::getAllAnimeNames() {
    QStringList animeNames;

    QSqlQuery query("SELECT Name FROM anime");
    while (query.next()) {
        animeNames << query.value(0).toString();
        qDebug() << query.value(0).toString();
    }

    return animeNames;
}

QStringList DataBase::getAnimeTitles(const QString &query)
{
    QStringList titles;

    QSqlQuery sqlQuery;
    sqlQuery.prepare("SELECT Name FROM anime WHERE Name LIKE (:query)");
    sqlQuery.bindValue(":query", "%" + query + "%");

    if (sqlQuery.exec()) {
        while (sqlQuery.next()) {
            titles.append(sqlQuery.value(0).toString());
        }
    } else {
        qDebug() << query << " ";
        qDebug() << "Error jopa:" << sqlQuery.lastError().text();
    }

    return titles;
}

bool DataBase::addOrUpdateReview(int userId, int animeId, const QString &comment, float rate, const QDate &date) {
    QSqlQuery query;

    // Проверка наличия отзыва от этого пользователя для данного аниме
    query.prepare("SELECT * FROM review WHERE User_id = :userId AND Anime_id = :animeId");
    query.bindValue(":userId", userId);
    query.bindValue(":animeId", animeId);
    if (query.exec() && query.next()) {
        // Если отзыв уже существует, обновляем его
        query.prepare("UPDATE review SET Comment = :comment, Rate = :rate, Date = :date "
                      "WHERE User_id = :userId AND Anime_id = :animeId");
    } else {
        // Если отзыва нет, добавляем новый
        query.prepare("INSERT INTO review (User_id, Anime_id, Comment, Rate, Date) "
                      "VALUES (:userId, :animeId, :comment, :rate, :date)");
    }

    query.bindValue(":userId", userId);
    query.bindValue(":animeId", animeId);
    query.bindValue(":comment", comment);
    query.bindValue(":rate", rate);
    query.bindValue(":date", date.toString("yyyy-MM-dd"));

    return query.exec();
}


