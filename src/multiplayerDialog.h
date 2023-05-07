#ifndef MULTIPLAYERDIALOG_H_
#define MULTIPLAYERDIALOG_H_

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
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
