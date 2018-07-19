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

// Variáveis globais
TemplateCache* templateCache;
HttpSessionStore* sessionStore;
StaticFileController* staticFileController;
FileLogger* logger; // Flag que indica se o servidor está rodando

// Protótipos das funções
int main(int argc, char *argv[]);
QString searchConfigFile();

// Função principal do programa
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

    // Se a resposta for "não"
    if (answer.startsWith('n', Qt::CaseInsensitive))
    {
        qDebug() << "> Digite o número da porta desejada: ";
        int port = s.readLine().toInt();

        // Se o número da porta digitado for inválido
        if (port < 80 || port > 49151)
            qDebug() << "Número de porta inválido! Usando a porta " << listenerSettings->value("port").toInt() << "..." << endl;
        else
            listenerSettings->setValue("port", port);
    }

    // Obtém o IP do servidor
    QString serverHost          = "127.0.0.1"; // Endereço IP padrão
    QList<QHostAddress> list    = QNetworkInterface::allAddresses();

    // Percorre todos os endereços da lista obtido da interface
    for (int nIter = 0; nIter < list.count(); nIter++)
    {
       if (!list[nIter].isLoopback())
          if (list[nIter].protocol() == QAbstractSocket::IPv4Protocol )
             serverHost = list[nIter].toString();
    }

    // Inicializa o servidor HTTP
    HttpListener *listener = new HttpListener(listenerSettings, new RequestMapper(&app), &app);

    // Se o listener não iniciou, encerra a execução
    if (!listener->isServerRunning())
        return 0;

    qWarning() << "=== Servidor Iniciado com IP " << serverHost << " na porta " << listenerSettings->value("port").toInt() << " ===";

    // Executa o código enquanto o terminal estiver aberto
    app.exec();

    qWarning("=== Servidor Encerrado ===");
}

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
            qDebug("Usando o arquivo de configuração %s",qPrintable(fileName));
            return fileName;
        }
    }

    // not found
    foreach (QString dir, searchList)
    {
        qWarning("%s/%s não encontrado",qPrintable(dir),qPrintable(fileName));
    }
    qFatal("Não foi possível localizar o arquivo de configuração %s",qPrintable(fileName));
    return 0;
}
