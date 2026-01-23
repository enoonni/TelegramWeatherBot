#include "telegram_bot.hpp"
#include "message_context.hpp"
#include <vector>

namespace telegram_bot
{

// http::HttpClient client;
//
// auto response = client.get("https://www.google.com/", {{"Accept", "html"}});
//
class TelegramBot::TelegramClientApi
{
  public:
    std::vector<dto::MessageContext> Update();

  private:
    std::vector<dto::MessageContext> message_queue_;
    int64_t last_update_id_ = 0;
};

enum class TelegramBot::TelegramBotState
{
    Initialize,
    Processing
};

TelegramBot::TelegramBot(std::string& token)
{
    this->token_ = token;
    this->state_ = TelegramBot::TelegramBotState::Initialize;
}

void TelegramBot::Poll()
{
    switch (this->state_)
    {
    case TelegramBot::TelegramBotState::Initialize:

        break;

    case TelegramBot::TelegramBotState::Processing:

        break;

    default:
        this->state_ = TelegramBot::TelegramBotState::Initialize;
        break;
    }
}

} // namespace telegram_bot
