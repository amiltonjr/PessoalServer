#ifndef APICONTROLLER_H
#define APICONTROLLER_H

#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"

using namespace amiltonjunior;

/**
  This controller generates a website using the template engine.
  It generates a Latin1 (ISO-8859-1) encoded website from a UTF-8 encoded template file.
*/

class ApiController : public HttpRequestHandler {
    Q_OBJECT
    Q_DISABLE_COPY(ApiController)
public:

    /** Constructor */
    ApiController();

    /** Generates the response */
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // APICONTROLLER_H
