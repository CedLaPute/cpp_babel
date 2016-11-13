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
#include <iostream>
#include <QComboBox>
#include <QSpinBox>

#include <QVector>

class window : public QWidget
{
  Q_OBJECT
 public:
  explicit window(QWidget *parent = 0);
  
 public slots:
   void		nameTaken();
   void		sndFailed();
   void		nameWrong();
   void		unknownName();
   void		callFailed();
   void		connectFailed();
     
   void		changeIp();
   void		changeNickname();

 signals:
   void		newName(QString const &);
   void		sndCall(QString const &);
   void		acceptCall();
   void		refuseCall();
   void		endCall();

 private:
    void        createMenu();
    void        createInfo();
    
    void        addBudy(QString);
    void        removeBudy(QString);

    void        calling(QString);

    QPushButton *b_server;
    QPushButton *b_nickname;
    QLineEdit   *ln_server;
    QLineEdit   *ln_nickname;

    QLabel      *infoClient;

    QMenu       *fileMenu;

    QGroupBox   *menu;
    QGroupBox   *info;

    std::vector<QString>    users;

    QGroupBox   *formGroupBox;
    QFormLayout *formLayout;

    QAction     *exitAction;
};

#endif // WINDOW_H
