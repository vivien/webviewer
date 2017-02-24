#ifndef WEBVIEWER_H
#define WEBVIEWER_H

#include <QUdpSocket>
#include <QWebEngineView>

class WebViewer : public QObject {

	Q_OBJECT

public:
	WebViewer(QObject *parent = 0) : QObject(parent) {}

	void initBrowser(const QUrl &url);
	void initServer(const QHostAddress &host, quint16 port);

public slots:
	void readPendingDatagrams();

private:
	QUdpSocket *sock;
	QWebEngineView *view;
};

#endif /* WEBVIEWER_H */
