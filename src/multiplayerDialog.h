#ifndef MULTIPLAYERDIALOG_H_
#define MULTIPLAYERDIALOG_H_

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include "server.h"
class MultiplayerDialog: public QDialog {
    Q_OBJECT

    public:
        explicit MultiplayerDialog(QWidget *parent = nullptr);

    private slots:
        void onCreateServerButtonClicked();
        Client* onConnectToServerButtonClicked();
        void onInputChanged();
		void closeEvent(QCloseEvent *event) override;
    private:
        QPushButton *createServerButton;
        QPushButton *connectToServerButton;
        QLineEdit *serverPortInput;
        QLineEdit *serverAddressInput;
        QLineEdit *connectPortInput;
		QSharedPointer<Server> server;
	signals:
		void windowClosed();
};

#endif
