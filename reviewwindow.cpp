#include "reviewwindow.h"
#include "ui_reviewwindow.h"

reviewwindow::reviewwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::reviewwindow)
{
    ui->setupUi(this);
}

//void reviewwindow::addReviewButtonClicked() {
//    int userId = getCurrentUserId(); // Замените этот метод на ваш способ получения userId
//    int animeId = getCurrentAnimeId(); // Замените этот метод на ваш способ получения animeId
//    QString comment = ui->textBrowser->toPlainText(); // Получение текста из QTextBrowser
//    float rate = static_cast<float>(ui->comboBox->currentIndex() + 1); // Получение оценки из ComboBox (плюс 1, так как индексы начинаются с 0)

//    bool success = database.addOrUpdateReview(userId, animeId, comment, rate, QDate::currentDate());
//    if (success) {
//        // Отзыв успешно добавлен или обновлен
//    } else {
//        // Произошла ошибка при добавлении отзыва
//    }
//}
reviewwindow::~reviewwindow()
{
    delete ui;
}
