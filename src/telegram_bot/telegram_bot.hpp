#pragma once
#include "telegram_bot/telegram_client_api/telegram_client_api.hpp"
#include <string>

namespace telegrambot
{
class TelegramBot
{
  public:
    explicit TelegramBot(std::string token);
    void poll();
    void sendMessage(std::string message, int64_t user_id);

  private:
    class TelegramClientApi;
    enum class TelegramBotState;
    TelegramBotState state_;
    std::string token_;
    int64_t last_update_id_;
    telegramclientapi::TelegramClientApi telegram_client_api_;
};
} // namespace telegrambot
