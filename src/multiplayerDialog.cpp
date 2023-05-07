#include "mainwindow.h"
#include "mainmenu.h"
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
  connect(this, &MultiplayerDialog::windowClosed, parent, &MainMenu::show);
}

void MultiplayerDialog::onCreateServerButtonClicked() {
  QString levelPath = ((MainMenu*) this->parent())->getLevelPath();
  this->server = QSharedPointer<Server>::create(this, serverPortInput->text().toInt(), levelPath);
  qDebug() << "Create server with port:" << serverPortInput->text();
}

Client* MultiplayerDialog::onConnectToServerButtonClicked() {
  Client* client = new Client(this, serverAddressInput->text(), connectPortInput->text().toInt());
  return client;
}

void MultiplayerDialog::onInputChanged() {
  createServerButton->setEnabled(!serverPortInput->text().isEmpty());
  connectToServerButton->setEnabled(!serverAddressInput->text().isEmpty() && !connectPortInput->text().isEmpty());
}

void MultiplayerDialog::closeEvent(QCloseEvent *event) {
	emit windowClosed();
	event->accept();
}
