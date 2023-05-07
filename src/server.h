#pragma once

#include <QTcpServer>
#include <QTcpSocket>
#include <QCoreApplication>
#include <QObject>
#include "client.h"


class Server : public QObject {
	Q_OBJECT
public:
	explicit Server(QObject* parent, int port = 9999);
	~Server();
	void send(std::string message);

private slots:
	// automatically triggered when server can read data i guess
	void readData();
	// automatically triggered when client disconnects
	void disconnected();

private:
	int port;
	QTcpServer* server;
	// the connected client
};
