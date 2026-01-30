#include "telegram_bot.hpp"
#include <iostream>

namespace telegrambot
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

void TelegramBot::poll()
{
    switch (this->state_)
    {
    case TelegramBotState::Initialize:
    {
        auto updates = this->telegram_client_api_.Update(this->token_);
        if (!updates.empty())
        {
            this->last_update_id_ = updates[updates.size() - 1].update_id;
            this->state_ = TelegramBotState::Processing;
        }

        break;
    }

    case TelegramBotState::Processing:
    {
        auto updates = this->telegram_client_api_.Update(this->token_, this->last_update_id_ + 1);

        if (!updates.empty())
        {
            this->last_update_id_ = updates[updates.size() - 1].update_id;
            for (const auto& update : updates)
            {
                std::cout << update.text << "\n";
            }
        }
        break;
    }

    default:
    {
        this->state_ = TelegramBotState::Initialize;
        break;
    }
    }
}

} // namespace telegrambot
