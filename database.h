#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>
#include <QDebug>

class DataBase
{
public:
    DataBase();
    ~DataBase();

    bool openDatabase();
    void closeDatabase();

    bool dropUserAccountTable();

    bool addAnime(const QString &name, int year, const QString &genreId, const QString &studioName, const QString &description);
    bool addAnimeGenre(int animeId, bool comedy, bool drama, bool adventure, bool horror);
    bool addReview(int userId, int animeId, const QString &comment, float rate, const QDate &date);

    QVector<QString> getTop3AnimeByRating();
    QString getAnimeDescriptionByName(const QString &animeName);
    QString getAnimeInfo(const QString &animeName);
    QString getGenreNameById(int genreId);
    QStringList getAllAnimeNames();
    QStringList getAnimeTitles(const QString &query);
    bool addOrUpdateReview(int userId, int animeId, const QString &comment, float rate, const QDate &date);

    bool createUsersTable();
    bool createFavoriteAnimeListTable();
    bool createAnimePageTable();
    bool createPictureSourceTable();
    bool createVideoSourceTable();
    bool createAnimeTable();
    bool createReviewTable();
    bool createGenresTable();
    bool setForeignKeys();

    bool insertUser(const QString &username, const QString &login, const QString &password);
    bool checkUser(const QString &login, const QString &password);

    bool registerUser(const QString &username, const QString &login, const QString &password);
    bool checkUserExistence(const QString &login);

    QSqlDatabase getDatabase() const;

private:
    QSqlDatabase db;
};

#endif // DATABASE_H
