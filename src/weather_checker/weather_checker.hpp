#pragma once
#include <string>

namespace weatherchecker
{
class WeatherChecker
{
  public:
    void Poll();
    std::string GetWeather();

  private:
    std::string last_weather_;
    const std::string WEATHER_URL_ = "https://api.open-meteo.com/v1/forecast?latitude=45.0097&longitude=41.9228&current_weather=true";
};

} // namespace weatherchecker
