#ifndef REVIEWWINDOW_H
#define REVIEWWINDOW_H

#include <QMainWindow>

namespace Ui {
class reviewwindow;
}

class reviewwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit reviewwindow(QWidget *parent = nullptr);
    void addReviewButtonClicked();
    ~reviewwindow();

private:
    Ui::reviewwindow *ui;
};

#endif // REVIEWWINDOW_H
