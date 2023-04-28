#include <QTcpSocket>
#include <QCoreApplication>
class Client : public QObject {
    Q_OBJECT

public:
    Client(QObject *parent = nullptr);
    ~Client();
	void connectToSession(QString ip, int port); 

private slots:
    void onConnected();
    void onReadyRead();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError socketError);

private:
    QTcpSocket *socket;
};
