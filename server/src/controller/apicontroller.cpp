#include "apicontroller.h"

ApiController::ApiController()
{}

void ApiController::service(HttpRequest& request, HttpResponse& response)
{
    // Processa os dados recebidos
    QByteArray dt = request.getParameter("data");
    QString data = dt.constData();

    qDebug() << "data = " << data;

    // Processa a resposta
    response.setHeader("Content-Type", "application/json");

    // Verifica se recebeu os dados
    if (data.length() > 5)
    {
        response.write("{\"result\":\"OK\"}");
    }
    else
    {
        response.write("{\"result\":\"ERROR\"}");
    }
}
