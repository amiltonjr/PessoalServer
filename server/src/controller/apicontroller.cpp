#include "apicontroller.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QObject>

ApiController::ApiController()
{}

void ApiController::service(HttpRequest& request, HttpResponse& response)
{
    // Processa os dados recebidos
    QByteArray dt = request.getParameter("data");
    QString data = dt.constData();

    //qDebug() << "data = " << data;

    // Processa a resposta
    response.setHeader("Content-Type", "application/json");

    // Verifica se recebeu os dados
    if (data.length() > 5)
    {
        response.write("{\"result\":\"OK\"}");

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
            qDebug() << "Idade: " << obj["age"].toString();
            qDebug() << "Sexo: " << obj["sex"].toString() << endl;
        }
    }
    else
    {
        response.write("{\"result\":\"ERROR\"}");
    }
}
