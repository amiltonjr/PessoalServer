#include "apicontroller.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QList>
#include <QJsonArray>
#include <QObject>

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
    QByteArray dt = request.getParameter("data");
    QString data = dt.constData();

    //qDebug() << "data = " << data;

    // Define o cabeçalho de resposta
    response.setHeader("Content-Type", "application/json; charset=utf-8");

    // Verifica se recebeu dados
    if (data.length() > 5)
    {
        // Status OK
        response.setStatus(200, "OK");
        response.write("{\"response\":{\"code\":200,\"description\":\"OK\"}}");

        qDebug() << "> Dados recebidos pela API:" << endl;

        // Converte os dados recebidos para JSON
        QJsonDocument jsonResponse = QJsonDocument::fromJson(data.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();

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
