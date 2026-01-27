#pragma once
#include "telegram_bot/dto/message_context.hpp"
#include <cstdint>
#include <vector>

namespace telegram_bot::telegram_client_api
{
class TelegramClientApi
{
  public:
    std::vector<telegram_bot::dto::MessageContext> Update(std::string token);
    std::vector<telegram_bot::dto::MessageContext> Update(std::string token, int64_t offset);

  private:
};
} // namespace telegram_bot::telegram_client_api
