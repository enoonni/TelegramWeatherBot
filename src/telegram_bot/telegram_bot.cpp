#include "telegram_bot.hpp"

namespace telegram_bot
{

enum class TelegramBot::TelegramBotState
{
    Initialize,
    Processing
};

TelegramBot::TelegramBot(std::string token)
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
