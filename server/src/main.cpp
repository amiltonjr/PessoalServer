#include <QCoreApplication>
#include <QNetworkInterface>
#include <QDir>
#include "httplistener.h"
#include "templatecache.h"
#include "httpsessionstore.h"
#include "staticfilecontroller.h"
#include "filelogger.h"
#include "requestmapper.h"

using namespace amiltonjunior;

/** Cache for template files */
TemplateCache* templateCache;

/** Storage for session cookies */
HttpSessionStore* sessionStore;

/** Controller for static files */
StaticFileController* staticFileController;

/** Redirects log messages to a file */
FileLogger* logger;


/** Search the configuration file */
QString searchConfigFile()
{
    QString binDir=QCoreApplication::applicationDirPath();
    QString appName=QCoreApplication::applicationName();
    QString fileName(appName+".ini");

    QStringList searchList;
    searchList.append(binDir);
    searchList.append(binDir+"/etc");
    searchList.append(binDir+"/../etc");
    searchList.append(binDir+"/../../etc"); // for development without shadow build
    searchList.append(binDir+"/../"+appName+"/etc"); // for development with shadow build
    searchList.append(binDir+"/../../"+appName+"/etc"); // for development with shadow build
    searchList.append(binDir+"/../../../"+appName+"/etc"); // for development with shadow build
    searchList.append(binDir+"/../../../../"+appName+"/etc"); // for development with shadow build
    searchList.append(binDir+"/../../../../../"+appName+"/etc"); // for development with shadow build
    searchList.append(QDir::rootPath()+"etc/opt");
    searchList.append(QDir::rootPath()+"etc");

    foreach (QString dir, searchList)
    {
        QFile file(dir+"/"+fileName);
        if (file.exists())
        {
            // found
            fileName=QDir(file.fileName()).canonicalPath();
            qDebug("Using config file %s",qPrintable(fileName));
            return fileName;
        }
    }

    // not found
    foreach (QString dir, searchList)
    {
        qWarning("%s/%s not found",qPrintable(dir),qPrintable(fileName));
    }
    qFatal("Cannot find config file %s",qPrintable(fileName));
    return 0;
}


/**
  Entry point of the program.
*/
int main(int argc, char *argv[])
{
    QCoreApplication app(argc,argv);

    app.setApplicationName("Server");
    app.setOrganizationName("AmiltonJr");

    // Mensagem de boas-vindas
    qDebug() << endl << "=== SERVIDOR - CADASTRO DE PESSOAL ===" << endl << endl;

    // Find the configuration file
    QString configFileName=searchConfigFile();

    // Configure logging into a file
    /*
    QSettings* logSettings=new QSettings(configFileName,QSettings::IniFormat,&app);
    logSettings->beginGroup("logging");
    FileLogger* logger=new FileLogger(logSettings,10000,&app);
    logger->installMsgHandler();
    */

    // Configure template loader and cache
    QSettings* templateSettings=new QSettings(configFileName,QSettings::IniFormat,&app);
    templateSettings->beginGroup("templates");
    templateCache=new TemplateCache(templateSettings,&app);

    // Configure session store
    QSettings* sessionSettings=new QSettings(configFileName,QSettings::IniFormat,&app);
    sessionSettings->beginGroup("sessions");
    sessionStore=new HttpSessionStore(sessionSettings,&app);

    // Configure static file controller
    QSettings* fileSettings=new QSettings(configFileName,QSettings::IniFormat,&app);
    fileSettings->beginGroup("docroot");
    staticFileController=new StaticFileController(fileSettings,&app);

    // Configure and start the TCP listener
    QSettings* listenerSettings=new QSettings(configFileName,QSettings::IniFormat,&app);
    listenerSettings->beginGroup("listener");

    // Pergunta ao usuário se deseja alterar a porta do servidor
    QTextStream s(stdin);
    qDebug() << "A porta padrão selecionada é: " << listenerSettings->value("port").toInt() << endl;
    qDebug() << "> Deseja utilizar essa porta? (S/N): ";
    QString answer = s.readLine();

    if (answer.startsWith('n', Qt::CaseInsensitive))
    {
        qDebug() << "> Digite o número da porta desejada: ";
        int port = s.readLine().toInt();

        // Valida o número da porta digitado
        if (port < 80 || port > 49151)
        {
            qDebug() << "Número de porta inválido! Usando a porta " << listenerSettings->value("port").toInt() << "..." << endl;
        }
        else
        {
            listenerSettings->setValue("port", port);
        }
    }

    // Obtém o IP do servidor
    QString serverHost = "127.0.0.1";
    QList<QHostAddress> list = QNetworkInterface::allAddresses();

    for (int nIter = 0; nIter < list.count(); nIter++)
    {
       if (!list[nIter].isLoopback())
          if (list[nIter].protocol() == QAbstractSocket::IPv4Protocol )
             serverHost = list[nIter].toString();
    }

    new HttpListener(listenerSettings, new RequestMapper(&app), &app);

    qWarning() << "=== Servidor Iniciado com IP " << serverHost << " na porta " << listenerSettings->value("port").toInt() << " ===";

    app.exec();

    qWarning("=== Servidor Encerrado ===");
}
