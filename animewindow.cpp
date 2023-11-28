#include "animewindow.h"

AnimeWindow::AnimeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AnimeWindow)
{
    ui->setupUi(this);

    connect(ui->listWidget, &QListWidget::itemSelectionChanged, this, &AnimeWindow::showAnimeInfoOnSelection);
    QVector<QString> top3Anime = dbManager->getTop3AnimeByRating();
    QListWidget *animeListWidget = ui->listWidget;
    for (const QString &animeName : top3Anime) {
        QListWidgetItem *item = new QListWidgetItem(animeName);
        animeListWidget->addItem(item);
    }

    findCompleter = new QCompleter(this);
    findCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    findCompleter->setFilterMode(Qt::MatchContains); // Фильтрация по частичному совпадению
    ui->lineEdit->setCompleter(findCompleter);


    connect(ui->lineEdit, &QLineEdit::textChanged, this, [this](const QString& text){
        QStringList titles = dbManager->getAnimeTitles(text);
        findCompleter->setModel(new QStringListModel(titles, findCompleter));
    });

    connect(ui->lineEdit, &QLineEdit::returnPressed, this, [this](){
        QString text = ui->lineEdit->text();
        onAnimeSelected(text);
    });
    connect(findCompleter, QOverload<const QString &>::of(&QCompleter::activated), this, &AnimeWindow::onAnimeSelected);

    //QStringList animeNames = dbManager->getAllAnimeNames(); // Получение списка названий аниме из базы данных
    //findCompleter->setModel(new QStringListModel(animeNames, findCompleter));


//    // Добавление QListWidget на форму или layout в AnimeWindow
//    QVBoxLayout *layout = new QVBoxLayout(this);
//    layout->addWidget(animeListWidget);
//    setLayout(layout);

}
void AnimeWindow::showAnimeInfoOnSelection() {
    QListWidgetItem *selectedItem = ui->listWidget->currentItem();
    if (selectedItem) {
        QString animeName = selectedItem->text();
        QString animeInfo = dbManager->getAnimeInfo(animeName); // Получить информацию об аниме
        qDebug() << "ВОТ ЭТО 1 " << animeInfo << " ";
        showAnimeInfoWidget(animeInfo); // Отобразить окно с информацией об аниме
    }
}

AnimeWindow::~AnimeWindow()
{
    delete ui;
}

QString AnimeWindow::getAnimeDescription(const QString &animeName) {
    // Ваш код для получения описания аниме по его имени из базы данных
    // Например, запрос к базе данных по имени аниме для получения описания
    // Предположим, что у вас есть функция getAnimeDescriptionByName в базе данных
    QString description = dbManager->getAnimeDescriptionByName(animeName);
    return description;
}

void AnimeWindow::showAnimeInfoWidget(const QString &animeInfo) {
    if(animeInfoWidget)
    {
        animeInfoWidget->hide();
        delete animeInfoWidget;
    }

    qDebug() << "ВОТ ЭТО 2 " << animeInfo << " ";

    animeInfoWidget = new animepage(this);

    animeInfoWidget->setWindowModality(Qt::ApplicationModal);
    animeInfoWidget->receiveAnimeInfo(animeInfo);
    animeInfoWidget->setAllLabels();

    animeInfoWidget->show();
}
void AnimeWindow::onAnimeSelected(const QString &text)
{
    QStringList titles = dbManager->getAnimeTitles(text);

    // Проверка, существует ли аниме
    if (titles.contains(text, Qt::CaseInsensitive)) {
        // Если аниме существует, создаем и показываем окно
        QString animeInfo = dbManager->getAnimeInfo(text);
        showAnimeInfoWidget(animeInfo);
    } else {
        // Если аниме не найдено, выводим сообщение об ошибке
        QMessageBox::warning(this, "Anime Not Found", "The anime '" + text + "' was not found.");
    }
}



