#include "window.h"
#include "Network.h"

window::window(QWidget *parent) : QWidget(parent)
{
  createMenu();
  createInfo();
  
  QVBoxLayout *mainLayout = new QVBoxLayout;
  
  mainLayout->addWidget(menu);
  mainLayout->addWidget(info);
  
  setLayout(mainLayout);
  
  setWindowTitle(tr("Babel"));
}

void    window::createInfo()
{
    info = new QGroupBox(tr("Info"));
    QFormLayout *layout = new QFormLayout;
    infoClient = new QLabel;

    layout->addWidget(infoClient);
    info->setLayout(layout);
}

void    window::createMenu()
{
    menu = new QGroupBox(tr("Menu"));
    QGridLayout *layout = new QGridLayout;

    b_call = new QPushButton("Call", this);
    ln_call = new QLineEdit(this);
    b_nickname = new QPushButton("Nickname", this);
    ln_nickname = new QLineEdit(this);

    layout->addWidget(b_call, 1, 0);
    layout->addWidget(b_nickname, 1, 1);
    layout->addWidget(ln_call, 0, 0);
    layout->addWidget(ln_nickname, 0, 1);
    menu->setLayout(layout);

    connect(b_call,SIGNAL(clicked()),this,SLOT(call()));
    connect(b_nickname,SIGNAL(clicked()),this,SLOT(changeNickname()));
}

void    window::listLogin(QLabel *list)
{
    infoClient->setText(list);
}

void    window::call()
{
    bool    bl = false;
    QMessageBox disp;
    QString text;

    if (!QString(ln_call->text()).isEmpty())
    {
        unsigned int i = 0;
        while (i < users.size())
        {
            if (QString::compare(users[i], ln_call->text(), Qt::CaseInsensitive) == 0)
                bl = true;
            ++i;
        }
        if (bl == true)
        {
            text += "You're calling ";
            text += ln_call->text();
            text += ".\nClick on \"Cancel\" will ring off the call.";
            disp.setText(text);
            disp.setStandardButtons(QMessageBox::Cancel);
            emit sndCall(ln_call->text());
            disp.exec();
            emit endCall();
        }
        else
        {
            text += "This user isn't on the server.";
            disp.setText(text);
            disp.setStandardButtons(QMessageBox::Cancel);
            disp.exec();
        }
    }
}

void    window::changeNickname()
{
    if (!QString(ln_nickname->text()).isEmpty())
    {
        QMessageBox disp;
        disp.setWindowTitle("New NickName");
        disp.setText(this->ln_nickname->text());
        emit newName(this->ln_nickname->text());
        disp.exec();
        emit newName(this->ln_nickname->text());
    }
}

void    window::calling(QString name)
{
    QString text;
    QMessageBox::StandardButton reply;

    text += name;
    text += " is calling you.\nWant to ring on ?";
    reply = QMessageBox::question(this,"Call", text, QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        text = "You're calling ";
        text += name;
        text += ".\nClick on \"Cancel\" will ring off the call.";
        emit acceptCall();
        QMessageBox(QMessageBox::Information, "Call", text, QMessageBox::Cancel).exec();
    }
    else
        emit refuseCall();
}

void		window::nameTaken()
{
<<<<<<< HEAD
    QMessageBox disp;
    disp.setIcon(QMessageBox::Critical);
    disp.setText("This name is already taken.");
    disp.exec();
=======
  std::cout << "name taken ma gueule" << std::endl;
>>>>>>> 5608c71992187ef462e8d656490e751804399fba
}

void		window::sndFailed()
{
    QMessageBox disp;
    disp.setIcon(QMessageBox::Critical);
    disp.setText("Signal send has failed.");
    disp.exec();
}

void		window::nameWrong()
{
    QMessageBox disp;
    disp.setIcon(QMessageBox::Critical);
    disp.setText("This name is invalide (too long).");
    disp.exec();
}

void		window::unknownName()
{
    QMessageBox disp;
    disp.setIcon(QMessageBox::Critical);
    disp.setText("This name is unknown.");
    disp.exec();
}

void		window::callFailed()
{
    QMessageBox disp;
    disp.setIcon(QMessageBox::Critical);
    disp.setText("The call has failed.");
    disp.exec();
}

void		window::connectFailed()
{
    QMessageBox disp;
    disp.setIcon(QMessageBox::Critical);
    disp.setText("The connexion has failed.");
    disp.exec();
}
