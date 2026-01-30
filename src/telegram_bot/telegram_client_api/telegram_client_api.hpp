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

  private:
};
} // namespace telegrambot::telegramclientapi
