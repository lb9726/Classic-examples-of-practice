#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <string>
#include <vector>
#include "Happy.h"
#include "Array.h"
using std::string;
using std::vector;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    init();

    vector<Array> VVI;
    VVI.push_back(VI);
    ui->lineEditVI->setText(bit_to_QString(VVI));

    connect(ui->pushButtonEncode, SIGNAL(clicked(bool)),
            this, SLOT(showCode()));
    connect(ui->pushButtonSetKey, SIGNAL(clicked(bool)),
            this, SLOT(setKey()));
    connect(ui->pushButtonECB, SIGNAL(clicked(bool)),
            this, SLOT(decodeECB()));
    connect(ui->pushButtonCBC, SIGNAL(clicked(bool)),
            this, SLOT(decodeCBC()));
    connect(ui->pushButtonCFB, SIGNAL(clicked(bool)),
            this, SLOT(decodeCFB()));
    connect(ui->pushButtonOFB, SIGNAL(clicked(bool)),
            this, SLOT(decodeOFB()));
    connect(ui->pushButtonCTR, SIGNAL(clicked(bool)),
            this, SLOT(decodeCTR()));

    connect(ui->pushButtonClearECB, SIGNAL(clicked(bool)),
            this, SLOT(clearECB()));
    connect(ui->pushButtonClearCBC, SIGNAL(clicked(bool)),
            this, SLOT(clearCBC()));
    connect(ui->pushButtonClearCFB, SIGNAL(clicked(bool)),
            this, SLOT(clearCFB()));
    connect(ui->pushButtonClearOFB, SIGNAL(clicked(bool)),
            this, SLOT(clearOFB()));
    connect(ui->pushButtonClearCTR, SIGNAL(clicked(bool)),
            this, SLOT(clearCTR()));
}

Widget::~Widget()
{
    delete ui;
}


/************************************
 *让各个密码的文本框显示密文
************************************/
void Widget::showCode()
{
    QString qs = ui->lineEditPlaintext->text();
    string s = qs.toStdString();


    //ECB
    qs = bit_to_QString(encode_ECB(s));
    ui->lineEditECB->setText(qs);

    //CBC
    qs = bit_to_QString(encode_CBC(s));
    ui->lineEditCBC->setText(qs);

    //CFB
    qs = bit_to_QString(encode_CFB(s));
    ui->lineEditCFB->setText(qs);

    //OFB
    qs = bit_to_QString(encode_OFB(s));
    ui->lineEditOFB->setText(qs);

    //CTR
    qs = bit_to_QString(encode_CTR(s));
    ui->lineEditCTR->setText(qs);
}

/************************
 * 5种解码方式
************************/
void Widget::decodeECB()
{
    vector<Array> v = QString_to_bit(ui->lineEditECB->text());
    string s = decode_ECB(v);
    ui->lineEditECB->setText(QString::fromStdString(s));
}

void Widget::decodeCBC()
{
    vector<Array> v = QString_to_bit(ui->lineEditCBC->text());
    string s = decode_CBC(v);
    ui->lineEditCBC->setText(QString::fromStdString(s));
}

void Widget::decodeCFB()
{
    vector<Array> v = QString_to_bit(ui->lineEditCFB->text());
    string s = decode_CFB(v);
    ui->lineEditCFB->setText(QString::fromStdString(s));
}

void Widget::decodeOFB()
{
    vector<Array> v = QString_to_bit(ui->lineEditOFB->text());
    string s = decode_OFB(v);
    ui->lineEditOFB->setText(QString::fromStdString(s));
}

void Widget::decodeCTR()
{
    vector<Array> v = QString_to_bit(ui->lineEditCTR->text());
    string s = decode_CTR(v);
    ui->lineEditCTR->setText(QString::fromStdString(s));
}


/********************************
 * 输入密钥
********************************/
void Widget::setKey()
{
    QString qs = ui->lineEditKey->text();
    if (qs.size() == 0)
        return;
    if (qs.size() < 8) {
        ui->lineEditKey->setText(QString::fromStdString("密钥为8字符！"));
        return;
    }
    key = string_to_bit(qs.toStdString())[1];
    make_key();
    ui->lineEditKey->setText(QString::fromStdString("已设置！"));
}



/********************************
 * 清空各个槽
********************************/
void Widget::clearECB()
{
    ui->lineEditECB->clear();
}

void Widget::clearCBC()
{
    ui->lineEditCBC->clear();
}

void Widget::clearCFB()
{
    ui->lineEditCFB->clear();
}

void Widget::clearOFB()
{
    ui->lineEditOFB->clear();
}

void Widget::clearCTR()
{
    ui->lineEditCTR->clear();
}


/********************************
 *用于将比特数组转为QString
 *为了让密文框显示比特
********************************/
QString Widget::bit_to_QString(const vector<Array> &v)
{
    string res;
    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < 64; j++)
        {
            if (v[i].get(j) == 0)
                res += '0';
            else
                res += '1';
            if ((j+1)%8 == 0)
                res += ' ';
        }
    }
    return QString::fromStdString(res);
}



/********************************
 * 将QString转化为vector<Array>
 * 用于将密文框里的QString转为数组
*********************************/
vector<Array> Widget::QString_to_bit(const QString &qs)
{
    vector<Array> res;
    res.push_back(Array(64));
    int index = 0;
    int block = 0;
    for (int i = 0; i < qs.size(); i++)
    {
        if (qs.at(i) == ' ')
            continue;
        res[block][index++] = qs.at(i).toLatin1() - '0';
        if (index == 64 && qs.size()-i > 30) {
            index = 0;
            res.push_back(Array(64));
            block++;
        }
    }

    return res;
}




