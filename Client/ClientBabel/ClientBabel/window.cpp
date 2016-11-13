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

    b_server = new QPushButton("Call", this);
    ln_server = new QLineEdit(this);
    b_nickname = new QPushButton("Nickname", this);
    ln_nickname = new QLineEdit(this);

    layout->addWidget(b_server, 1, 0);
    layout->addWidget(b_nickname, 1, 1);
    layout->addWidget(ln_server, 0, 0);
    layout->addWidget(ln_nickname, 0, 1);
    menu->setLayout(layout);

    connect(b_server,SIGNAL(clicked()),this,SLOT(changeIp()));
    connect(b_nickname,SIGNAL(clicked()),this,SLOT(changeNickname()));
}

void    window::addBudy(QString name)
{
    if (!name.isEmpty())
    {
        QString list;
        users.push_back (name);
        for (unsigned i=0; i<users.size(); ++i)
        {
            list += users[i];
            list += "\n";
        }
        infoClient->setText(list);
    }
}

void    window::removeBudy(QString name)
{
    if (!name.isEmpty())
    {
        QString list;
        for (unsigned i=0; i<users.size(); ++i)
        {
            if (QString::compare(users[i], name, Qt::CaseInsensitive) == 0)
            {
                users.erase(users.begin()+i);
            }
        }
        for (unsigned i=0; i<users.size(); ++i)
        {
            list += users[i];
            list += "\n";
        }
        infoClient->setText(list);
    }
}

void    window::changeIp()
{
    bool    bl = false;
    QMessageBox disp;
    QString text;

    if (!QString(ln_server->text()).isEmpty())
    {
        unsigned int i = 0;
        while (i < users.size())
        {
            if (QString::compare(users[i], ln_server->text(), Qt::CaseInsensitive) == 0)
                bl = true;
            ++i;
        }
        if (bl == true)
        {
            text += "You're calling ";
            text += ln_server->text();
            text += ".\nClick on \"Cancel\" will ring off the call.";
            disp.setText(text);
            disp.setStandardButtons(QMessageBox::Cancel);
            disp.exec();
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
        calling("bernar");
        QMessageBox disp;
        disp.setText(this->ln_nickname->text());
        disp.exec();
    }
}

void    window::calling(QString name)
{
    QString text;
    QMessageBox::StandardButton reply;

    emit sndName(QString("hope"));
    text += name;
    text += " is calling you.\nWant to ring on ?";
    reply = QMessageBox::question(this,"Call", text, QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        text = "You're calling ";
        text += name;
        text += ".\nClick on \"Cancel\" will ring off the call.";
        QMessageBox(QMessageBox::Information, "Call", text, QMessageBox::Cancel).exec();
    }
}

void	window::sig(QString const &s)
{
  std::cout << s.toStdString() << std::endl;
}
