#pragma once
#include "telegram_bot/telegram_client_api/telegram_client_api.hpp"
#include <string>

namespace telegram_bot
{
class TelegramBot
{
  public:
    explicit TelegramBot(std::string token);
    void Poll();

  private:
    class TelegramClientApi;
    enum class TelegramBotState;
    TelegramBotState state_;
    std::string token_;
    int64_t last_update_id_;
    telegram_client_api::TelegramClientApi telegram_client_api_;
};
} // namespace telegram_bot
