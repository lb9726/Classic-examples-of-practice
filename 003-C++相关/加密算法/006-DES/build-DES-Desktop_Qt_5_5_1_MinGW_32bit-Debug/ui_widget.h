/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLineEdit *lineEditPlaintext;
    QLineEdit *lineEditKey;
    QLineEdit *lineEditECB;
    QLineEdit *lineEditCBC;
    QLineEdit *lineEditCFB;
    QLineEdit *lineEditOFB;
    QLineEdit *lineEditCTR;
    QPushButton *pushButtonEncode;
    QPushButton *pushButtonECB;
    QPushButton *pushButtonCBC;
    QPushButton *pushButtonCFB;
    QPushButton *pushButtonOFB;
    QPushButton *pushButtonCTR;
    QPushButton *pushButtonSetKey;
    QPushButton *pushButtonClearECB;
    QPushButton *pushButtonClearCBC;
    QPushButton *pushButtonClearCFB;
    QPushButton *pushButtonClearOFB;
    QPushButton *pushButtonClearCTR;
    QLineEdit *lineEditVI;
    QLabel *label;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(944, 520);
        lineEditPlaintext = new QLineEdit(Widget);
        lineEditPlaintext->setObjectName(QStringLiteral("lineEditPlaintext"));
        lineEditPlaintext->setGeometry(QRect(80, 70, 801, 23));
        lineEditKey = new QLineEdit(Widget);
        lineEditKey->setObjectName(QStringLiteral("lineEditKey"));
        lineEditKey->setGeometry(QRect(80, 130, 221, 23));
        lineEditKey->setMaxLength(8);
        lineEditECB = new QLineEdit(Widget);
        lineEditECB->setObjectName(QStringLiteral("lineEditECB"));
        lineEditECB->setGeometry(QRect(80, 200, 681, 23));
        lineEditCBC = new QLineEdit(Widget);
        lineEditCBC->setObjectName(QStringLiteral("lineEditCBC"));
        lineEditCBC->setGeometry(QRect(80, 250, 681, 23));
        lineEditCFB = new QLineEdit(Widget);
        lineEditCFB->setObjectName(QStringLiteral("lineEditCFB"));
        lineEditCFB->setGeometry(QRect(80, 300, 681, 23));
        lineEditOFB = new QLineEdit(Widget);
        lineEditOFB->setObjectName(QStringLiteral("lineEditOFB"));
        lineEditOFB->setGeometry(QRect(80, 350, 681, 23));
        lineEditCTR = new QLineEdit(Widget);
        lineEditCTR->setObjectName(QStringLiteral("lineEditCTR"));
        lineEditCTR->setGeometry(QRect(80, 400, 681, 23));
        pushButtonEncode = new QPushButton(Widget);
        pushButtonEncode->setObjectName(QStringLiteral("pushButtonEncode"));
        pushButtonEncode->setGeometry(QRect(460, 130, 89, 24));
        pushButtonECB = new QPushButton(Widget);
        pushButtonECB->setObjectName(QStringLiteral("pushButtonECB"));
        pushButtonECB->setGeometry(QRect(790, 200, 89, 24));
        pushButtonCBC = new QPushButton(Widget);
        pushButtonCBC->setObjectName(QStringLiteral("pushButtonCBC"));
        pushButtonCBC->setGeometry(QRect(790, 250, 89, 24));
        pushButtonCFB = new QPushButton(Widget);
        pushButtonCFB->setObjectName(QStringLiteral("pushButtonCFB"));
        pushButtonCFB->setGeometry(QRect(790, 300, 89, 24));
        pushButtonOFB = new QPushButton(Widget);
        pushButtonOFB->setObjectName(QStringLiteral("pushButtonOFB"));
        pushButtonOFB->setGeometry(QRect(790, 350, 89, 24));
        pushButtonCTR = new QPushButton(Widget);
        pushButtonCTR->setObjectName(QStringLiteral("pushButtonCTR"));
        pushButtonCTR->setGeometry(QRect(790, 400, 89, 24));
        pushButtonSetKey = new QPushButton(Widget);
        pushButtonSetKey->setObjectName(QStringLiteral("pushButtonSetKey"));
        pushButtonSetKey->setGeometry(QRect(340, 130, 89, 24));
        pushButtonClearECB = new QPushButton(Widget);
        pushButtonClearECB->setObjectName(QStringLiteral("pushButtonClearECB"));
        pushButtonClearECB->setGeometry(QRect(20, 200, 41, 24));
        pushButtonClearCBC = new QPushButton(Widget);
        pushButtonClearCBC->setObjectName(QStringLiteral("pushButtonClearCBC"));
        pushButtonClearCBC->setGeometry(QRect(20, 250, 41, 24));
        pushButtonClearCFB = new QPushButton(Widget);
        pushButtonClearCFB->setObjectName(QStringLiteral("pushButtonClearCFB"));
        pushButtonClearCFB->setGeometry(QRect(20, 300, 41, 24));
        pushButtonClearOFB = new QPushButton(Widget);
        pushButtonClearOFB->setObjectName(QStringLiteral("pushButtonClearOFB"));
        pushButtonClearOFB->setGeometry(QRect(20, 350, 41, 24));
        pushButtonClearCTR = new QPushButton(Widget);
        pushButtonClearCTR->setObjectName(QStringLiteral("pushButtonClearCTR"));
        pushButtonClearCTR->setGeometry(QRect(20, 400, 41, 24));
        lineEditVI = new QLineEdit(Widget);
        lineEditVI->setObjectName(QStringLiteral("lineEditVI"));
        lineEditVI->setGeometry(QRect(80, 460, 681, 23));
        label = new QLabel(Widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 461, 41, 20));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0));
        lineEditPlaintext->setInputMask(QString());
        lineEditPlaintext->setText(QString());
        lineEditPlaintext->setPlaceholderText(QApplication::translate("Widget", "\346\230\216\346\226\207", 0));
        lineEditKey->setPlaceholderText(QApplication::translate("Widget", "\345\257\206\351\222\245", 0));
        lineEditECB->setPlaceholderText(QApplication::translate("Widget", "ECB\345\257\206\346\226\207", 0));
        lineEditCBC->setPlaceholderText(QApplication::translate("Widget", "CBC\345\257\206\346\226\207", 0));
        lineEditCFB->setPlaceholderText(QApplication::translate("Widget", "CFB\345\257\206\346\226\207", 0));
        lineEditOFB->setPlaceholderText(QApplication::translate("Widget", "OFB\345\257\206\346\226\207", 0));
        lineEditCTR->setPlaceholderText(QApplication::translate("Widget", "CTR\345\257\206\346\226\207", 0));
        pushButtonEncode->setText(QApplication::translate("Widget", "\345\212\240\345\257\206", 0));
        pushButtonECB->setText(QApplication::translate("Widget", "ECB\350\247\243\345\257\206", 0));
        pushButtonCBC->setText(QApplication::translate("Widget", "CBC\350\247\243\345\257\206", 0));
        pushButtonCFB->setText(QApplication::translate("Widget", "CFB\350\247\243\345\257\206", 0));
        pushButtonOFB->setText(QApplication::translate("Widget", "OFB\350\247\243\345\257\206", 0));
        pushButtonCTR->setText(QApplication::translate("Widget", "CTR\350\247\243\345\257\206", 0));
        pushButtonSetKey->setText(QApplication::translate("Widget", "\350\256\276\347\275\256\345\257\206\351\222\245", 0));
        pushButtonClearECB->setText(QApplication::translate("Widget", "\346\270\205\347\251\272", 0));
        pushButtonClearCBC->setText(QApplication::translate("Widget", "\346\270\205\347\251\272", 0));
        pushButtonClearCFB->setText(QApplication::translate("Widget", "\346\270\205\347\251\272", 0));
        pushButtonClearOFB->setText(QApplication::translate("Widget", "\346\270\205\347\251\272", 0));
        pushButtonClearCTR->setText(QApplication::translate("Widget", "\346\270\205\347\251\272", 0));
        label->setText(QApplication::translate("Widget", "  VI", 0));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
