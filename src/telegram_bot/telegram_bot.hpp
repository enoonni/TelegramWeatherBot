#pragma once
#include "telegram_bot/telegram_client_api/telegram_client_api.hpp"
#include <string>

namespace telegrambot
{

class TelegramBot
{
  public:
    explicit TelegramBot(const std::string token);
    void poll();
    void sendMessage(std::string message, int64_t user_id);

  private:
    enum class TelegramBotState;
    enum class TelegramMessageCommand;
    TelegramBotState state_;
    std::string token_;
    int64_t last_update_id_;
    telegramclientapi::TelegramClientApi telegram_client_api_;
    TelegramBot::TelegramMessageCommand HandlingMessage(const std::string& message);
};

} // namespace telegrambot
