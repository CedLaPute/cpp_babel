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
#include <QGridLayout>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QFormLayout>
#include <QString>
#include <vector>
#include <string>

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
    void        createInfo();

    void        addBudy();

    QPushButton *b_server;
    QPushButton *b_nickname;
    QLineEdit   *ln_server;
    QLineEdit   *ln_nickname;

    /*
     * changer le type de stockage pour qu'avec le vector cela creer une liste cliquable
     * gerer l'ouverture d'une fenettre en cas de demande d'appel
     * autre chose ?
    */
    QLabel      *infoClient;

    QMenu       *fileMenu;

    QGroupBox   *menu;
    QGroupBox   *info;

    std::vector<QString>    users;

    QAction     *exitAction;
};

#endif // WINDOW_H
