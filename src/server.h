#pragma once

#include <QTcpServer>
#include <QTcpSocket>
#include <QCoreApplication>
#include <QObject>
#include "client.h"
#include <QDialog>
#include <QWidget>


// TODO comment
class Server : public QObject {
	Q_OBJECT
public:
	explicit Server(QObject* parent = 0, int port = 9999, QString levelPath="./levels/level.txt");
	~Server();

private slots:
	// Automatically triggered when new client connects
	void newConnection();
	// automatically triggered when server can read data i guess
	void readData();
	// automatically triggered when client disconnects
	void disconnected();

private:
	int port;
	QTcpServer* server;
	// the connected client
	QTcpSocket* client = nullptr;
	QString levelPath;
};
