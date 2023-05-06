#include "multiplayerDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>

MultiplayerDialog::MultiplayerDialog(QWidget *parent) : QDialog(parent) {
  QVBoxLayout *mainLayout = new QVBoxLayout(this);

  QLabel *createServerLabel = new QLabel("Create a server", this);
  mainLayout->addWidget(createServerLabel);

  QHBoxLayout *serverLayout = new QHBoxLayout();
  createServerButton = new QPushButton("Create Server", this);
  createServerButton->setEnabled(false);
  connect(createServerButton, &QPushButton::clicked, this, &MultiplayerDialog::onCreateServerButtonClicked);
  serverPortInput = new QLineEdit(this);
  serverPortInput->setPlaceholderText("Server Port");
  serverLayout->addWidget(createServerButton);
  serverLayout->addWidget(serverPortInput);
  mainLayout->addLayout(serverLayout);


  QLabel *connectToServerLabel = new QLabel("Connect to Server", this);
  mainLayout->addWidget(connectToServerLabel);

  QHBoxLayout *clientLayout = new QHBoxLayout();
  connectToServerButton = new QPushButton("Connect to Server", this);
  connectToServerButton->setEnabled(false);
  connect(connectToServerButton, &QPushButton::clicked, this, &MultiplayerDialog::onConnectToServerButtonClicked);
  serverAddressInput = new QLineEdit(this);
  serverAddressInput->setPlaceholderText("Server Address");
  connectPortInput = new QLineEdit(this);
  connectPortInput->setPlaceholderText("Server Port");
  clientLayout->addWidget(connectToServerButton);
  clientLayout->addWidget(serverAddressInput);
  clientLayout->addWidget(connectPortInput);
  mainLayout->addLayout(clientLayout);

  connect(serverPortInput, &QLineEdit::textChanged, this, &MultiplayerDialog::onInputChanged);
  connect(serverAddressInput, &QLineEdit::textChanged, this, &MultiplayerDialog::onInputChanged);
  connect(connectPortInput, &QLineEdit::textChanged, this, &MultiplayerDialog::onInputChanged);
}

void MultiplayerDialog::onCreateServerButtonClicked() {
  qDebug() << "Create server with port:" << serverPortInput->text();
}

void MultiplayerDialog::onConnectToServerButtonClicked() {
  qDebug() << "Connect to server with address:" << serverAddressInput->text() << "and port:" << connectPortInput->text();
}

void MultiplayerDialog::onInputChanged() {
  createServerButton->setEnabled(!serverPortInput->text().isEmpty());
  connectToServerButton->setEnabled(!serverAddressInput->text().isEmpty() && !connectPortInput->text().isEmpty());
}
