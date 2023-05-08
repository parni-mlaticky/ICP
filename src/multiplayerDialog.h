/** 
 * @file multiplayerDialog.h
 * @brief Header for the MultiplayerDialog window
 * @authors Ondřej Zobal, Petr Kolouch
 * */

#ifndef MULTIPLAYERDIALOG_H_
#define MULTIPLAYERDIALOG_H_

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>
#include "mainwindow.h"

// TODO comment
/** 
 * @class MultiplayerDialog
 * @brief Class for the MultiplayerDialog window, which is used to create a server or connect to one
 * */
class MultiplayerDialog: public QDialog {
    Q_OBJECT

    public:
        explicit MultiplayerDialog(QWidget *parent = nullptr);

    private slots:
        void onCreateServerButtonClicked();
        void onConnectToServerButtonClicked();
        void onInputChanged();
		void closeEvent(QCloseEvent *event) override;
    private:
        QPushButton *createServerButton;
        QPushButton *connectToServerButton;
        QLineEdit *serverPortInput;
        QLineEdit *serverAddressInput;
        QLineEdit *connectPortInput;
	signals:
		void windowClosed();
        void connectionChosen(bool hosting, std::string host, int port);
};

#endif
