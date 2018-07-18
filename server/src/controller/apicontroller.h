#ifndef APICONTROLLER_H
#define APICONTROLLER_H

#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"

using namespace amiltonjunior;

class ApiController : public HttpRequestHandler {
    Q_OBJECT
    Q_DISABLE_COPY(ApiController)
public:

    // Método construtor
    ApiController();

    // Método que faz o controle do serviço da API
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // APICONTROLLER_H
