#include "window.hh"

window::window(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    //personnal = new QGroupBox(tr("Personnal info"));
    QHBoxLayout *layout= new QHBoxLayout;
//    layout->addRow(new QLabel(tr("Line 1:")), new QLineEdit);
//    layout->addRow(new QLabel(tr("Line 2, long text:")), new QComboBox);
//    layout->addRow(new QLabel(tr("Line 3:")), new QSpinBox);

    b_server = new QPushButton("Connexion", this);
    ln_server = new QLineEdit(this);
    b_nickname = new QPushButton("Nickname", this);
    ln_nickname = new QLineEdit(this);

//    b_server->setGeometry(5, 5, 100, 25);
//    b_nickname->setGeometry(110, 5, 100, 25);
//    ln_server->setGeometry(5, 31, 100, 25);
//    ln_nickname->setGeometry(110, 31, 100, 25);

    mainLayout->addWidget(b_server);
    mainLayout->addWidget(b_nickname);
    mainLayout->addWidget(ln_server);
    mainLayout->addWidget(ln_nickname);
    setLayout(mainLayout);


    connect(b_server,SIGNAL(clicked()),this,SLOT(changeIp()));
    connect(b_nickname,SIGNAL(clicked()),this,SLOT(changeNickname()));
}

void    window::changeIp()
{
    QMessageBox disp;
    disp.setText(this->ln_server->text());
    disp.exec();
}

void    window::changeNickname()
{
    QMessageBox disp;
    disp.setText(this->ln_nickname->text());
    disp.exec();
}
