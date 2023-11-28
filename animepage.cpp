#include "animepage.h"
#include "ui_animepage.h"

animepage::animepage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::animepage)
{

    ui->setupUi(this);
    connect(ui->makeReview, &QPushButton::clicked, this, &animepage::makeReviewButtonClicked);

}

void animepage::setAllLabels() {
    QLabel *titleLabel = ui->enterName;
    QLabel *yearLabel = ui->enterYear;
    QLabel *ratingLabel = ui->enterGrade;
    QLabel *genresLabel = ui->enterGenres;
    qDebug() << animeInformation << " ";
    QStringList animeInfoList = animeInformation.split(",");



    qDebug() << animeInfoList.size() << " ";
    if (animeInfoList.size() == 4) {
        qDebug() << "??";
        qDebug() << animeInfoList[0] << animeInfoList[1] << animeInfoList[2] << animeInfoList[3];
        titleLabel->setText(animeInfoList[0]);
        yearLabel->setText(animeInfoList[1]);
        ratingLabel->setText(animeInfoList[3]);
        genresLabel->setText(animeInfoList[2]);
    }
}
void animepage::makeReviewButtonClicked() {
    if(windowForReview)
    {
        windowForReview->hide();
        delete windowForReview;
    }

    windowForReview = new reviewwindow(this);

    windowForReview->setWindowModality(Qt::ApplicationModal);

    windowForReview->show();
}



animepage::~animepage()
{
    delete ui;
}
