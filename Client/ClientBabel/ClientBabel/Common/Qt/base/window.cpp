#include "window.hh"

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

    b_server = new QPushButton("Connexion", this);
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

void    window::addBudy()
{
    if (!QString(ln_server->text()).isEmpty())
    {
        QString list;
        users.push_back (ln_server->text());
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
    if (!QString(ln_server->text()).isEmpty())
    {
        QMessageBox disp;
        disp.setText(this->ln_server->text());
        disp.exec();
    }
}

void    window::changeNickname()
{
    /*
     * prototy de fonction rm de la lite
    */
//    if (!QString(ln_nickname->text()).isEmpty())
//    {
//        QString list;
//        for (unsigned i=0; i<users.size(); ++i)
//        {
//            if (QString::compare(users[i], ln_nickname->text(), Qt::CaseInsensitive) == 0)
//            {
//                std::cout << "bonjour" << std::endl;
//            }
//        }
//        for (unsigned i=0; i<users.size(); ++i)
//        {
//            list += users[i];
//            list += "\n";
//        }
//        infoClient->setText(list);
        QMessageBox disp;
        disp.setText(this->ln_nickname->text());
        disp.exec();
//    }
}
