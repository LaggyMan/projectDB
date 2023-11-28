#ifndef ANIMEPAGE_H
#define ANIMEPAGE_H

#include <QMainWindow>
#include <QDebug>
#include "reviewwindow.h"

namespace Ui {
class animepage;
}

class animepage : public QMainWindow
{
    Q_OBJECT

public:
    explicit animepage(QWidget *parent = nullptr);
    void receiveAnimeInfo(const QString& info)
    {
        animeInformation = info;
    }
    void setAllLabels();
    void addReviewButtonClicked();
    ~animepage();

private:
    Ui::animepage *ui;
    QString animeInformation;
    reviewwindow* windowForReview;
    void makeReviewButtonClicked();
};

#endif // ANIMEPAGE_H
