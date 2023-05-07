#include "server.h"
#include "mainwindow.h"
#include <QDialog>
#include <QWidget>
Server::Server(QObject* parent, int port) : QObject(parent) {
	server = new QTcpServer(this);
	connect(server, SIGNAL(newConnection()), parent, SLOT(on_connected_to_client()));
	if (!server->listen(QHostAddress::Any, port)) {
		qDebug() << "Server could not start";
	} 
	else {
		qDebug() << "Server started!";
		qDebug() << "Listening on " << server->serverAddress() << ":" << server->serverPort();
	}
	this->levelPath = levelPath;
	newConnection();
}


Server::~Server() {
	delete server;
}

void Server::newConnection() {
	this->client = server->nextPendingConnection();
	// connect(client, SIGNAL(readyRead()), this, SLOT(readData()));
	// connect(client, SIGNAL(disconnected()), this, SLOT(disconnected()));
	qDebug() << "New client connected!";
	// this->client->write("Hello client!");
	// this->client->flush();
	// QFile file(this->levelPath);
	// file.open(QIODevice::ReadOnly);
    // QTextStream in(&file);
	// QString level = in.readAll();
	// MainWindow* mainWindow = new MainWindow(level, nullptr, this, nullptr);
    // connect(mainWindow, SIGNAL(windowClosed()), this->parent()->parent(), SLOT(onMainWindowClosed()));
	// mainWindow->show();
	// ((QWidget*)this->parent()->parent())->hide();
}

void Server::readData() {
	QByteArray data = client->readAll();
	qDebug() << "Data in: " << data;
}

void Server::disconnected() {
	qDebug() << "Client disconnected!";
	client->deleteLater();
}

void Server::send(std::string message) {
	this->client->write(message.c_str());
}
