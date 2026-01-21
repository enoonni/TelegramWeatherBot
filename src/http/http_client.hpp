#pragma once
#include <map>
#include <string>
// #include <system_error>

namespace http
{
struct Response
{
    long status = 0;
    std::string body;
};

class HttpClient
{
  public:
    Response get(const std::string& url, const std::map<std::string, std::string>& headers);
    Response post(
        const std::string& url,
        const std::string& body,
        const std::map<std::string, std::string>& headers = {});
};
} // namespace http
