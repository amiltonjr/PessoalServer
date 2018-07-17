#include "apicontroller.h"
//#include "templatecache.h"
//#include "template.h"

/** Cache for template files */
//extern TemplateCache* templateCache;

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


    /* DESATIVADA A RESPOSTA PADRÃO DA BIBLIOTECA
    response.setHeader("Content-Type", "text/html; charset=ISO-8859-1");

    Template t=templateCache->getTemplate("demo",request.getHeader("Accept-Language"));
    t.enableWarnings();
    t.setVariable("path",request.getPath());

    QMap<QByteArray,QByteArray> headers=request.getHeaderMap();
    QMapIterator<QByteArray,QByteArray> iterator(headers);
    t.loop("header",headers.size());
    int i=0;
    while (iterator.hasNext())
    {
        iterator.next();
        t.setVariable(QString("header%1.name").arg(i),QString(iterator.key()));
        t.setVariable(QString("header%1.value").arg(i),QString(iterator.value()));
        ++i;
    }

    response.write(t.toLatin1(),true);
    */
}
