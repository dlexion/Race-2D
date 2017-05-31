#include "startwindow.h"

StartWindow::StartWindow(QObject *parent) : QWidget()
{

    this->setFixedSize(800,600);
    this->setWindowTitle("Race 2D");
    this->setWindowIcon(QIcon("pictures/Icon.png"));
    QPalette qp;
    qp.setBrush( this->backgroundRole() ,QBrush(QPixmap("pictures/road.png")));
    this->setPalette(qp);

    start=new QPushButton("Start");
    start->setAutoDefault(true);

    edit = new QPushButton("Edit nickname");
    edit->setAutoDefault(true);

    exit= new QPushButton("Exit");
    exit->setAutoDefault(true);

    qgl = new QGridLayout;
    qgl->setMargin(260);
    qgl->addWidget(start, 0, 0);
    qgl->addWidget(edit,1,0);
    qgl->addWidget(exit,2,0);

    this->setLayout(qgl);

    connect(exit,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(edit,SIGNAL(clicked(bool)),this,SLOT(slotEditName()));
    connect(start,SIGNAL(clicked(bool)),this,SLOT(slotStartGame()));

    readNick();
    update();
    this->show();
}

void StartWindow::slotStartGame()
{
    Game* game = new Game(nickname);
    this->close();

}

void StartWindow::slotEditName()
{
    bool ok;
    QString str = QInputDialog::getText( 0,
                                         "Input",
                                         "New nickname:",
                                         QLineEdit::Normal,
                                         "",
                                         &ok
                                         );
    if(ok && !str.isEmpty()){
        nickname = str;
        update();
    }
    saveNick();

}

void StartWindow::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
    int x=400- (nickname.size()+8)*5;
    paint.setFont(QFont("Times",15,QFont::Normal));
    paint.drawText(x,20, "Player: " + nickname);
    paint.drawText(20,480,"Сontrol:");
    paint.drawText(20,500,"W - speed up");
    paint.drawText(20,520,"S - speed down");
    paint.drawText(20,540,"A - left");
    paint.drawText(20,560,"D - right");
    paint.drawText(20,580,"Esc - pause");
}

void StartWindow::readNick()
{
    QFile file("name.txt");
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);
        stream >> nickname;
    }
    if(nickname.isEmpty()){
        nickname = "player";
    }
    file.close();
}

void StartWindow::saveNick()
{
    QFile file("name.txt");
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        stream << nickname;
    }
    file.close();
}

StartWindow::~StartWindow()
{
    delete[] start;
    delete[] edit;
    delete[] exit;
    delete[] qgl;
}
