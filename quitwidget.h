#ifndef QUITWIDGET_H
#define QUITWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class QuitWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QuitWidget(QWidget *parent = 0);
    ~QuitWidget();
     QPushButton* quit_ok;

private:
    QLabel* quit_message;
    QPushButton* quit_cancel;
};

#endif // QUITWIDGET_H
