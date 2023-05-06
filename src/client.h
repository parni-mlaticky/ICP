#pragma once

#include <QCoreApplication>
#include <QTcpSocket>
class Client : public QObject {
  Q_OBJECT

public:
  Client(QObject *parent = nullptr, QString hostname = "", int port = 9999);
  ~Client();
  bool connectToSession();

private slots:
  // Automatically triggered when the client connects
  void onConnected();
  // Automatically triggered when the client can read data
  void onReadyRead();
  // Automatically triggered when the client disconnects
  void onDisconnected();
  void onError(QAbstractSocket::SocketError socketError);

private:
  // the socket bound to this client
  QTcpSocket *socket;
  // server's hostname
  QString hostname;
  // server's port
  int port;
  QString levelContent = "";
};
