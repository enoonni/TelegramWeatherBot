#include "weather_checker.hpp"
#include "http/http_client.hpp"
#include <cstddef>
#include <exception>
#include <nlohmann/json.hpp>
#include <string>

namespace weatherchecker
{
void WeatherChecker::Poll()
{
    try
    {
        http::HttpClient client;
        http::Response response = client.get(this->WEATHER_URL_, {});

        if (response.status != 200)
            return;

        if (!nlohmann::json::accept(response.body))
            return;

        auto json = nlohmann::json::parse(response.body);

        if (!json.contains("current_weather"))
            return;

        const auto& current_weather = json["current_weather"];

        int temperature = static_cast<int>(current_weather.value("temperature", 0.0));
        int wind = static_cast<int>(current_weather.value("windspeed", 0.0));

        this->last_weather_ = "Temperature: " + std::to_string(temperature) + "°C, " + "Wind: " + std::to_string(wind) + " m/s";
    }
    catch (const std::exception&)

    {
    }
}

std::string WeatherChecker::GetWeather()
{
    return this->last_weather_;
}
} // namespace weatherchecker
