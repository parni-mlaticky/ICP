#include "client.h"

Client::Client(QObject *parent) : QObject(parent) {
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::connected, this, &Client::onConnected);
    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &Client::onDisconnected);
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::error), this, &Client::onError);   
}

Client::~Client() {
    socket->disconnectFromHost();
    socket->deleteLater();
}

void Client::onConnected() {
    qDebug() << "Connected to server!";
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

void Client::connectToSession(QString ip, int port){
	socket->connectToHost(ip, port);
} 
