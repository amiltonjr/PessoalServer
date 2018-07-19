/******
 * SERVIDOR - CADASTRO DE PESSOAL
 * Criado por: Amilton Fontoura de Camargo Junior
 * Data: Julho de 2018
 *
 * Observação: Uma parte significativa do projeto foi criada usando a biblioteca
 * QtWebServer de Stefan Frings. Como o código fornecido pelo autor da biblioteca
 * não prejudica a funcionalidade do servidor de API, os comentários e métodos
 * criados pelo mesmo estão presentes no projeto, exceto nos scripts que foram
 * escritos especificamente para essa aplicação.
******/

#include "apicontroller.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QList>
#include <QJsonArray>
#include <QObject>
#include <QDateTime>

// Método construtor
ApiController::ApiController()
{}

// Método que faz o controle do serviço da API
// @param request - Ponteiro para o objeto HttpRequest da requisição
// @param response - Ponteiro para o objeto HttpResponse de resposta
// @return void
void ApiController::service(HttpRequest& request, HttpResponse& response)
{
    // Processa os dados recebidos
    QByteArray dt   = request.getParameter("data");
    QString data    = dt.constData();

    //qDebug() << "data = " << data << endl << "Method = " << request.getMethod();

    // Define o cabeçalho de resposta
    response.setHeader("Content-Type", "application/json; charset=utf-8");

    // Verifica se recebeu dados
    if (data.length() > 5)
    {
        // Status OK
        response.setStatus(200, "OK");
        response.write("{\"response\":{\"code\":200,\"description\":\"OK\"}}");

        qDebug() << QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss") << "> Dados recebidos pela API:" << endl;

        // Converte os dados recebidos para JSON
        QJsonDocument jsonResponse  = QJsonDocument::fromJson(data.toUtf8());
        QJsonObject jsonObject      = jsonResponse.object();

        // Obtém a lista de pessoas
        QJsonArray person = jsonObject["person"].toArray();

        // Percorre a lista de pessoas
        foreach (const QJsonValue & value, person) {
            // Converte os dados da pessoa para um objeto
            QJsonObject obj = value.toObject();

            // Imprime os dados no terminal
            qDebug() << "Nome: " << obj["name"].toString();
            qDebug() << "Idade: " << obj["age"].toInt();
            qDebug() << "Sexo: " << obj["sex"].toString() << endl;
        }
    }
    // Se não recebeu dados ou inválidos
    else
    {
        // Status de erro
        response.setStatus(405, "Entrada inválida");
        response.write("{\"response\":{\"code\":405,\"description\":\"Entrada inválida\"}}");

    }
}
