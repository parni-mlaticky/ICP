/********************************************************************************
** Form generated from reading UI file 'mainmenu.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINMENU_H
#define UI_MAINMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *playButton;
    QPushButton *multiplayerButton;
    QPushButton *selectLevelButton;
    QPushButton *replayButton;
    QPushButton *exitButton;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(800, 600);
        Form->setMaximumSize(QSize(800, 600));
        verticalLayoutWidget = new QWidget(Form);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(60, 40, 661, 511));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        playButton = new QPushButton(verticalLayoutWidget);
        playButton->setObjectName(QString::fromUtf8("playButton"));
        playButton->setFlat(false);

        verticalLayout->addWidget(playButton, 0, Qt::AlignHCenter);

        multiplayerButton = new QPushButton(verticalLayoutWidget);
        multiplayerButton->setObjectName(QString::fromUtf8("multiplayerButton"));

        verticalLayout->addWidget(multiplayerButton, 0, Qt::AlignHCenter);

        selectLevelButton = new QPushButton(verticalLayoutWidget);
        selectLevelButton->setObjectName(QString::fromUtf8("selectLevelButton"));
        selectLevelButton->setFlat(false);

        verticalLayout->addWidget(selectLevelButton, 0, Qt::AlignHCenter);

        replayButton = new QPushButton(verticalLayoutWidget);
        replayButton->setObjectName(QString::fromUtf8("replayButton"));

        verticalLayout->addWidget(replayButton, 0, Qt::AlignHCenter);

        exitButton = new QPushButton(verticalLayoutWidget);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));

        verticalLayout->addWidget(exitButton, 0, Qt::AlignHCenter);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        playButton->setText(QCoreApplication::translate("Form", "Play", nullptr));
        multiplayerButton->setText(QCoreApplication::translate("Form", "Multiplayer", nullptr));
        selectLevelButton->setText(QCoreApplication::translate("Form", "Select level", nullptr));
        replayButton->setText(QCoreApplication::translate("Form", "Replay", nullptr));
        exitButton->setText(QCoreApplication::translate("Form", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINMENU_H
