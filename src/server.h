#include <QTcpServer>
#include <QTcpSocket>
#include <QCoreApplication>
#include <QObject>

class Server : public QObject {
	Q_OBJECT
public:
	explicit Server(QObject* parent = 0);
	~Server();

private slots:
	void newConnection();
	void readData();
	void disconnected();

private:
	QTcpServer* server;
	QTcpSocket* client;
};
