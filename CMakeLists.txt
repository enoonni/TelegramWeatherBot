cmake_minimum_required(VERSION 3.10)
project(TelegramWeatherBot LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(SQLite3 REQUIRED)

add_executable(TelegramWeatherBot 
  src/main.cpp
  src/utils/signal_handler.cpp
  src/http/http_client.cpp
  src/config/config.cpp
  src/telegram_bot/telegram_bot.cpp
  src/telegram_bot/telegram_client_api/telegram_client_api.cpp
  src/weather_checker/weather_checker.cpp
  src/utils/stopwatch/stopwatch.cpp
  src/database/database.cpp
  src/database/sqlite/sqlite.cpp
)

target_include_directories(TelegramWeatherBot PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src/
  ${SQLite3_INCLUDE_DIRS}
)

target_link_libraries(TelegramWeatherBot PRIVATE
  CURL::libcurl
  nlohmann_json::nlohmann_json
  ${SQLite3_LIBRARIES}
)

install(
  TARGETS TelegramWeatherBot
  RUNTIME DESTINATION bin
)
