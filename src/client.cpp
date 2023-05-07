#include "client.h"
#include "mainwindow.h"
#include <QDialog>
#include <iostream>
#include <QThread>

Remote::Remote(QObject *parent, QString hostname, int port) : QObject(parent), message("") {
    this->socket = new QTcpSocket(this);
    this->parent = parent;
    this->connectSockets();
	this->hostname = hostname;
	this->port = port;
	this->connectToSession();
}

Remote::Remote(QObject* parent, int port) : QObject(parent) {
	this->server = new QTcpServer(this);
    this->socket = nullptr;
    this->parent = parent;
	if (!server->listen(QHostAddress::Any, port)) {
		qDebug() << "Server could not start";
	}
	else {
		qDebug() << "Server started!";
		qDebug() << "Listening on " << server->serverAddress() << ":" << server->serverPort();
	}
	connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));
	connect(this, SIGNAL(connected_to_client()), parent, SLOT(on_connected_to_client()));
}

void Remote::connectSockets() {
    connect(this->socket, SIGNAL(connected()), parent, SLOT(on_connected_to_server()));
    connect(this->socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(this, SIGNAL(onRecive(std::string)), parent, SLOT(onRecive(std::string)));
    connect(parent, SIGNAL(sendMessage(std::string)), this, SLOT(sendMessage(std::string)));
    connect(this->socket, &QTcpSocket::disconnected, this, &Remote::onDisconnected);
    connect(this->socket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::error), this, &Remote::onError);
}

void Remote::newConnection() {
	this->socket = server->nextPendingConnection();
    this->connectSockets();
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
    emit connected_to_client();
}


Remote::~Remote() {
	qDebug() << "Remote destructor called" << endl;
    socket->disconnectFromHost();
    socket->deleteLater();
}

void Remote::onConnected() {
    this->socket->write("Hello, server!");
}

void Remote::onReadyRead() {
    // QByteArray data = socket->readAll();
    // qDebug() << "Received data:" << data;
    // message += data.toStdString();
    auto message = this->socket->readAll().toStdString();
    std::cerr << "REMOTE: Recived message" << message << std::endl;
    emit onRecive(message);
}

void Remote::onDisconnected() {
    qDebug() << "Disconnected from server!";
}

void Remote::onError(QAbstractSocket::SocketError socketError) {
    qDebug() << "Socket error:" << socketError;
}

void Remote::makeMainWindow() {
}

// tries to connect to the server of timeouts after 3s 
// the commented part is the code that should be used to show the main window
// but it is a war crime 
bool Remote::connectToSession(){
    std::cerr << "Attempting to connect to" << this->hostname.toStdString() << ":" << this->port << std::endl;
	socket->connectToHost(this->hostname, this->port);
	if(socket->waitForConnected(3000)){
        qDebug() << "Connected to server with address:" << this->hostname  << "and port:" << this->port;
        return true;
	}
	else{
		qDebug() << "Not connected!";
		return false;
	}
}

std::string Remote::read() {
    // message += socket->readLine().toStdString();
    // auto iter = this->message.begin();
    // std::string out;
    // do {
    //     out += *iter;
    // } while (*iter != c || iter != message.end());

    // message = message.substr(out.size(), message.size() - out.size());

    // return out;

    return this->socket->readAll().toStdString();
}

int Remote::messageLength() {
    return this->message.size();
}

void Remote::sendMessage(std::string message) {
    std::cerr << "REMOTE: Sending message: " << message << std::endl;
    this->socket->write(QByteArray::fromStdString(message));
}
