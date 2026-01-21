#include "http_client.hpp"
#include <curl/curl.h>
#include <curl/easy.h>
#include <stdexcept>
#include <string>

namespace http
{

static size_t write_cb(void* contents, size_t size, size_t nmemb, void* userp)
{
    auto* str = static_cast<std::string*>(userp);
    str->append(static_cast<char*>(contents), size * nmemb);
    return size * nmemb;
}

Response HttpClient::post(
    const std::string& url,
    const std::string& body,
    const std::map<std::string, std::string>& headers)
{
    CURL* curl = curl_easy_init();
    if (!curl)
        throw std::runtime_error("curl init failed");

    Response resp;
    std::string response_body;

    struct curl_slist* header_list = nullptr;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_body);

    for (const auto& [k, v] : headers)
        header_list = curl_slist_append(
            header_list, (k + ": " + v).c_str());

    if (header_list)
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);

    curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &resp.status);

    resp.body = std::move(response_body);

    curl_slist_free_all(header_list);
    curl_easy_cleanup(curl);

    return resp;
}

Response HttpClient::get(const std::string& url, const std::map<std::string, std::string>& headers)
{
    CURL* curl = curl_easy_init();
    if (!curl)
        throw std::runtime_error("curl init failed");

    Response response;
    std::string response_body;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_body);

    struct curl_slist* header_list = nullptr;
    for (const auto& [k, v] : headers)
        header_list = curl_slist_append(
            header_list, (k + ": " + v).c_str());

    if (header_list)
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);

    CURLcode result = curl_easy_perform(curl);

    if (result != CURLE_OK)
    {
        curl_slist_free_all(header_list);
        curl_easy_cleanup(curl);
        throw std::runtime_error(curl_easy_strerror(result));
    }

    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response.status);
    response.body = std::move(response_body);

    curl_slist_free_all(header_list);
    curl_easy_cleanup(curl);

    return response;
}

} // namespace http
