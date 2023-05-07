#include "client.h"
#include "mainwindow.h"
#include <QDialog>

Client::Client(QObject *parent, QString hostname, int port) : QObject(parent) {
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::connected, this, &Client::onConnected);
    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &Client::onDisconnected);
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::error), this, &Client::onError);   
	this->hostname = hostname;
	this->port = port;
	this->connectToSession();
}

Client::~Client() {
	qDebug() << "Client destructor called" << endl;
    socket->disconnectFromHost();
    socket->deleteLater();
}

void Client::onConnected() {
    socket->write("Hello, server!");
}

void Client::onReadyRead() {
    QByteArray data = socket->readAll();
    qDebug() << "Received data:" << data;
}

void Client::onDisconnected() {
    qDebug() << "Disconnected from server!";
}

void Client::onError(QAbstractSocket::SocketError socketError) {
    qDebug() << "Socket error:" << socketError;
}

// tries to connect to the server of timeouts after 3s 
// the commented part is the code that should be used to show the main window
// but it is a war crime 
bool Client::connectToSession(){
	socket->connectToHost(this->hostname, this->port);
	if(socket->waitForConnected(3000)){
		qDebug() << "Connected to server with address:" << this->hostname  << "and port:" << this->port;
		/* auto mainWindow = new MainWindow(this->levelContent, this, nullptr, nullptr); */	
		/* mainWindow->show(); */
		/* connect(mainWindow, SIGNAL(windowClosed()), this->parent()->parent(), SLOT(onMainWindowClosed())); */
		/* ((QWidget*)this->parent()->parent())->hide(); */
		/* ((QDialog*)this->parent())->hide(); */
		/* return true; */
	}
	else{
		qDebug() << "Not connected!";
		return false;
	}
	return true;
} 
