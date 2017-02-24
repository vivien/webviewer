#include "WebViewer.h"

void WebViewer::initBrowser(const QUrl &url)
{
    view = new QWebEngineView();
    view->showFullScreen();
    view->setUrl(url);
}

void WebViewer::initServer(const QHostAddress &host, quint16 port)
{
    sock = new QUdpSocket();
    sock->bind(host, port);
    connect(sock, SIGNAL(readyRead()),this, SLOT(readPendingDatagrams()));
}

void WebViewer::readPendingDatagrams()
{
    QUrl url;

    while (sock->hasPendingDatagrams()) {
        QByteArray datagram;
        QString str;

        datagram.resize(sock->pendingDatagramSize());
        sock->readDatagram(datagram.data(), datagram.size());

        str = QString(datagram.data());
        url = QUrl(str.trimmed());
    }

    if (!url.isEmpty())
        view->setUrl(url);
}
