#include "config/config.hpp"
#include "database/database.hpp"
#include "telegram_bot/telegram_bot.hpp"
// #include "utils/signal_handler.hpp"
#include "utils/stopwatch/stopwatch.hpp"
#include "weather_checker/weather_checker.hpp"

#include <chrono>
// #include <iostream>
#include <memory>

enum class AppState
{
    ReadConfigPath,
    Initialize_db,
    Initialize,
    Ready
};

int main(int argc, char* argv[])
{
    // utils::SignalHandler signal_handler;
    AppState app_state = AppState::ReadConfigPath;
    db::Database db;
    std::string config_path = "bot_config.json";
    config::Config bot_config(config_path);
    weatherchecker::WeatherChecker checker;
    // telegrambot::TelegramBot bot(bot_config.GetToken());
    std::unique_ptr<telegrambot::TelegramBot> bot;
    utils::stopwatch::Stopwatch stopwatch(std::chrono::hours(1));
    utils::stopwatch::Stopwatch stopwatch_telegram_poll(std::chrono::seconds(10));

    // while (signal_handler.is_running())
    while (true)
    {
        switch (app_state)
        {
        case AppState::ReadConfigPath:
            if (bot_config.load())
            {
                bot = std::make_unique<telegrambot::TelegramBot>(bot_config.GetToken());
                app_state = AppState::Initialize_db;
            }
            else
            {
                // while (signal_handler.is_running())
                {
                }
                return 0;
            }
            break;

        case AppState::Initialize_db:
            if (db.initialize())
            {
                app_state = AppState::Ready;
            }
            else
            {
                // while (signal_handler.is_running())
                {
                }
                return 0;
            }
            break;

        case AppState::Ready:
            if (stopwatch_telegram_poll.expired())
            {
                bot->poll();
                stopwatch_telegram_poll.reset();
            }
            if (stopwatch.expired())
            {
                checker.poll();
                auto current_weather = checker.get_weather();
                auto users = db.get_users();
                for (auto user : users)
                {
                    bot->sendMessage(current_weather, user);
                }
                stopwatch.reset();
            }

            break;

        default:
            break;
        }
    }

    return 0;
}
