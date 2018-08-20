#include "collapseviewitem_contact.h"
#include "ui_collapseviewitem_contact.h"
#include <QDebug>

CollapseViewItem_Contact::CollapseViewItem_Contact(QString userName, QString titleText, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CollapseViewItem_Contact)
{
    ui->setupUi(this);

    if(ui->item_con->layout()!=0 )
    {
        qDebug()<<"ui->item_con->layout已经存在";
    }

    //给litteriem区域widget添加布局
    item_con_layout = new QVBoxLayout(this);
    item_con_layout->setContentsMargins(0,0,0,0);//设置上下左右的边距均为0
    item_con_layout->setSpacing(0);
    ui->item_con->setLayout(item_con_layout);


    ui->label->setProperty("slected",!ui->item_con->isVisible());

    this->setTitleText(titleText);

    user_db = QSqlDatabase::addDatabase("QSQLITE","connect3");
    user_db.setDatabaseName("D:/MyQTCode(Win32)/test/sqlmodel/RegisteredInfo.db");
    bool ok = user_db.open();
    qDebug()<<"数据库链接："<<ok;

    SqliteOperate sql_opr(user_db,this);
    friend_info_s = sql_opr.Get_ALL_Friend_Info(userName);
    qDebug()<<"friend_info_s.nickName_v  "<< friend_info_s.nickName_v.at(0);



//    //根据时间制作随机种子
//    QTime time;
//    time = QTime::currentTime();
//    qsrand(time.msec()+time.second()*1000);

//    //随机产生好友数目
//    int personNumber = qrand()%(MAX_PERSON_PIC_NUM)+1;
//    qDebug()<<"personNumber:"<<personNumber;

//    for(int i=0;i<personNumber;++i)
//    {
//        //随机选择好友头像
//        QString picPath = QString(":/media/person/media/person/%1.jpg")
//                .arg(QString::number(qrand()%(MAX_PERSON_PIC_NUM)+1));
//        addSubItem(new LitterIem(picPath,this));
//    }

//    //随机产生上线好友数目
//    int onlinePerson=qrand()%personNumber;

//    titleText = QString("%1 (%2/%3)")
//            .arg(titleText).arg(QString::number(onlinePerson)).arg(QString::number(personNumber));

//    this->setTitleText(titleText);

//    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(onCollapseButClick()));
}

CollapseViewItem_Contact::~CollapseViewItem_Contact()
{
    user_db.close();
    delete ui;
}

void CollapseViewItem_Contact::setTitleText(QString titleText)
{
    ui->pushButton->setText(titleText);
}

void CollapseViewItem_Contact::addSubItems(QList<QWidget *> widgets)
{
    foreach (QWidget *var, widgets) {
        addSubItem(var);
    }
}

void CollapseViewItem_Contact::addSubItem(QWidget *widget)
{
    item_con_layout->addWidget(widget);
}

void CollapseViewItem_Contact::onCollapseButClick()
{
    //设置为相反的显示状态
    ui->item_con->setVisible(!ui->item_con->isVisible());

    ui->label->setProperty("slected",ui->item_con->isVisible());

    ui->label->update();

}
