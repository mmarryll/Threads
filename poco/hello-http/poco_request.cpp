#include <string>
#include <iostream>
#include <fstream>

#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/URI.h>
#include <Poco/StreamCopier.h>

int main() {
    // create session
    Poco::URI uri("http://www.google.com");
    Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());

    // get path to resourse
    std::string path(uri.getPathAndQuery());
    if (path.empty()) {
        path = "/";
    }

    // create request
    Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET, path);
    session.sendRequest(request);

    // receive response
    Poco::Net::HTTPResponse response;
    std::istream& in = session.receiveResponse(response);

    // write response to file
    std::ofstream fout("page.html");
    Poco::StreamCopier::copyStream(in, fout);

    // report code
    std::cout << "Response code: " << response.getStatus() 
              << " " << response.getReason() << std::endl;
    return 0;
}