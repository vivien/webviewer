#include <QApplication>
#include <QCommandLineParser>
#include "WebViewer.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("WebViewer");
    QCoreApplication::setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("Fullscreen remote URL viewer");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption addressOption(QStringList() << "a" << "address", "Set the host address", "address");
    parser.addOption(addressOption);

    QCommandLineOption portOption(QStringList() << "p" << "port", "Set the UDP port", "port");
    parser.addOption(portOption);

    QCommandLineOption urlOption(QStringList() << "u" << "url", "Set the default URL", "url");
    parser.addOption(urlOption);

    parser.process(app);

    QHostAddress address = QHostAddress::Any;
    if (parser.isSet(addressOption))
        address = QHostAddress(parser.value(addressOption));
    qInfo() << "Address:" << address.toString();

    quint16 port = 7755;
    if (parser.isSet(portOption))
        port = parser.value(portOption).toInt();
    qInfo() << "Port:" << QString::number(port);

    QUrl url("file://" + app.applicationDirPath() + "/index.html");
    if (parser.isSet(urlOption))
        url = QUrl(parser.value(urlOption));
    qInfo() << "Default URL:" << url.toString();

    WebViewer view;
    view.initBrowser(QUrl(url));
    view.initServer(address, port);

    return app.exec();
}
