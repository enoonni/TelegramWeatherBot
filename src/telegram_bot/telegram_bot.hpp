#pragma once
#include <string>

namespace telegram_bot
{
class TelegramBot
{
  public:
    explicit TelegramBot(std::string& token);
    void Poll();

  private:
    class TelegramClientApi;
    enum class TelegramBotState;
    TelegramBotState state_;
    std::string token_;
};
} // namespace telegram_bot
