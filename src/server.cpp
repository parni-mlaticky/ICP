#include "server.h"

Server::Server(QObject* parent) : QObject(parent) {
	server = new QTcpServer(this);
	connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));
	QHostAddress address;
	address.setAddress("127.0.0.1");
	if (!server->listen(address, 9999)) {
		qDebug() << "Server could not start";
	} 
	else {
		qDebug() << "Server started!";
		qDebug() << "Listening on " << server->serverAddress() << ":" << server->serverPort();
	} 
}


Server::~Server() {
	delete server;
	delete client;
}

void Server::newConnection() {
	client = server->nextPendingConnection();
	connect(client, SIGNAL(readyRead()), this, SLOT(readData()));
	connect(client, SIGNAL(disconnected()), this, SLOT(disconnected()));
	qDebug() << "New client connected!";
}

void Server::readData() {
	QByteArray data = client->readAll();
	qDebug() << "Data in: " << data;
	client->write(data);
}

void Server::disconnected() {
	qDebug() << "Client disconnected!";
	client->deleteLater();
}


