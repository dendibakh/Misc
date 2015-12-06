#include "PaddingOracle.h"
#include "cpprest/http_client.h"
#include "utils.h"
#include <iostream>

using namespace web::http;
using namespace web::http::client;

ERROR_TYPE sendHTTPRequest(const std::string& str)
{
    
    http_client client(U(str));
    http_request request(methods::GET);
    client.request(request).then([](http_response response)
    {
        // Perform actions here to inspect the HTTP response...
        std::cout << "response: " << response.to_string() << std::endl;
        if(response.status_code() == status_codes::OK)
        {
        }
	else if (response.status_code() == status_codes::Forbidden)
	{
		return ERROR_TYPE_PADDING;
	}
    });
    
    return ERROR_TYPE_SUCCESS;
}
