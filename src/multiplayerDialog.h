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

    private:
        QPushButton *createServerButton;
        QPushButton *connectToServerButton;
        QLineEdit *serverPortInput;
        QLineEdit *serverAddressInput;
        QLineEdit *connectPortInput;
};

#endif
