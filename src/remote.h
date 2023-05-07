#pragma once

#include <QCoreApplication>
#include <QTcpSocket>
#include <QTcpServer>

class Remote : public QObject {
  Q_OBJECT


// TODO comment

public:
  Remote(QObject *parent = nullptr, QString hostname = "", int port = 9999);
	explicit Remote(QObject* parent, int port = 9999);
  ~Remote();
  bool connectToSession();
  void makeMainWindow();
  std::string read();
  int messageLength();

private slots:
  // Client Automatically triggered when the client connects
  void onConnected();
	// Server Automatically triggered when new client connects
	void newConnection();
  // Automatically triggered when the client can read data
  void onReadyRead();
  // Automatically triggered when the client disconnects
  void onDisconnected();
  void onError(QAbstractSocket::SocketError socketError);

signals:
    void onRecive(std::string);
    void connected_to_client();

public slots:
    void sendMessage(std::string message);

private:
  void connectSockets();
  QObject* parent;
  // the socket bound to this client
  QTcpSocket *socket;
  QTcpServer *server;
  // server's hostname
  QString hostname;
  // server's port
  int port;
  QString levelContent = "";
  std::string message;
};
