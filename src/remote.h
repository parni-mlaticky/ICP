/**
 * @file remote.h
 * @brief Header for the Remote class
 * @authors Ondřej Zobal, Vladimír Hucovič
 * */

#pragma once

#include <QCoreApplication>
#include <QTcpSocket>
#include <QTcpServer>

/**
 * @class Remote
 * @brief Class for communication between computers. Used in multiplayer
 */
class Remote : public QObject {
  Q_OBJECT

public:
  /**
   * @param parent Parent QObject
   * @param hostname Hostname to connect to
   * @param port Port to connect to
   * */
  Remote(QObject *parent = nullptr, QString hostname = "", int port = 9999);
  /**
   * @param parent Parent QObject
   * @param port Port to host on
   * */
	explicit Remote(QObject* parent, int port = 9999);
  ~Remote();
  /**
   * @brief Tries to connect to a server
   * @return true if connection was succesfull, false if not
   * */
  bool connectToSession();
  /**
   * @brief Reads data recived from the connected device
   * @return Data send by the other device
   * */
  std::string read();

private slots:
  /**
   * @brief Triggered when new client connects
   * */
	void newConnection();
  // Automatically triggered when the client can read data
  /**
   * @brief Triggered when data becomes ready to be read
   * this message is forwared to the parrent
   * */
  void onReadyRead();
  /**
   * @brief Triggered when the other clinet is disconnected
   * */
  void onDisconnected();
  /**
   * @brief Triggered on error
   * @param socketError Error information
   * */
  void onError(QAbstractSocket::SocketError socketError);

signals:
    void onRecive(std::string);
  /**
   * @brief Emitted when new client connects
   * */
    void connected_to_client();

public slots:
  /**
   * @brief Handles sending messages
   * @param message The message that will be sent to the other connected party
   * */
    void sendMessage(std::string message);

private:
  /**
   * @brief Connects signals and slots that are used for both the server and the client
   * */
  void connectSockets();
  /**
   * @brief The parent QObject
   * */
  QObject* parent;
  /**
   * @brief Connected socket
   * */
  QTcpSocket *socket;
  /**
   * @brief The server object. Is always nullptr on the client.
   * */
  QTcpServer *server;
  /**
   * @brief The hostname to connect to.
   * */
  QString hostname;
  /**
   * @brief The port
   * */
  int port;
  std::string message;
};
