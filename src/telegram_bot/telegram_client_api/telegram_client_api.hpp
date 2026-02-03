#pragma once
#include "telegram_bot/dto/message_context.hpp"
#include <cstdint>
#include <vector>

namespace telegrambot::telegramclientapi
{
class TelegramClientApi
{
  public:
    std::vector<telegrambot::dto::MessageContext> Update(std::string token);
    std::vector<telegrambot::dto::MessageContext> Update(std::string token, int64_t offset);

    void sendMessage(const std::string& token, int64_t user_id, const std::string& text);

  private:
};
} // namespace telegrambot::telegramclientapi
