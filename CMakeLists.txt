cmake_minimum_required(VERSION 3.10)
project(TelegramWeatherBot LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(TelegramWeatherBot 
  src/main.cpp
  src/utils/signal_handler.cpp
  src/http/http_client.cpp
  src/config/config.cpp
  src/telegram_bot/telegram_bot.cpp
)

target_include_directories(TelegramWeatherBot PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src/
  ${CMAKE_CURRENT_SOURCE_DIR}/src/config/
  ${CMAKE_CURRENT_SOURCE_DIR}/src/http/
  ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/
  ${CMAKE_CURRENT_SOURCE_DIR}/src/telegram_bot/
  ${CMAKE_CURRENT_SOURCE_DIR}/src/telegram_bot/dto/
)

target_link_libraries(TelegramWeatherBot PRIVATE
  CURL::libcurl
  nlohmann_json::nlohmann_json
)

install(
  TARGETS TelegramWeatherBot
  RUNTIME DESTINATION bin
)
