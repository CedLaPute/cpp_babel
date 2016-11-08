#ifndef WINDOW_H
#define WINDOW_H

#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QMessageBox>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>

class window : public QWidget
{
    Q_OBJECT
public:
    explicit window(QWidget *parent = 0);

signals:

public slots:
    void changeIp();
    void changeNickname();

private:
    void        createMenu();

    QPushButton *b_server;
    QPushButton *b_nickname;
    QLineEdit   *ln_server;
    QLineEdit   *ln_nickname;

    QGroupBox  *personnal;
};

#endif // WINDOW_H
