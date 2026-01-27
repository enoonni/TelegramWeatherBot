#pragma once
#include "telegram_bot/dto/message_context.hpp"
#include <vector>

namespace telegram_bot::telegram_client_api
{
class TelegramClientApi
{
  public:
    std::vector<telegram_bot::dto::MessageContext> Update(std::string token);

  private:
    std::vector<telegram_bot::dto::MessageContext> message_queue_;
    int64_t last_update_id_ = 0;
};
} // namespace telegram_bot::telegram_client_api
