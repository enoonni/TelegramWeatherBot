#include "telegram_bot.hpp"
#include "database/database.hpp"
#include <iostream>

namespace telegrambot
{

enum class TelegramBot::TelegramBotState
{
    Initialize,
    Processing
};

enum class TelegramBot::TelegramMessageCommand
{
    Unknown,
    Registration,
    CancelRegistration
};

TelegramBot::TelegramBot(const std::string token)
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
        try
        {
            auto updates = this->telegram_client_api_.Update(this->token_);
            if (!updates.empty())
            {
                this->last_update_id_ = updates.back().update_id;
            }
            else
            {
                this->last_update_id_ = 0;
            }
            this->state_ = TelegramBotState::Processing;
        }
        catch (const std::exception&)
        {
            std::cout << "\n Exception from telegram bot updates initialize\n";
        }

        break;
    }

    case TelegramBotState::Processing:
    {
        std::vector<telegrambot::dto::MessageContext> updates;
        if (this->last_update_id_ != 0)
            updates = this->telegram_client_api_.Update(this->token_, this->last_update_id_ + 1);
        else
            updates = this->telegram_client_api_.Update(this->token_);

        if (!updates.empty())
        {
            std::cout << "updates is not empty\n";
            this->last_update_id_ = updates[updates.size() - 1].update_id;
            for (const auto& update : updates)
            {
                std::cout << update.text << "\n";
                auto command = HandlingMessage(update.text);
                switch (command)
                {
                case TelegramBot::TelegramMessageCommand::Registration:
                {
                    bool is_new_user = true;
                    db::Database db;
                    auto users = db.get_users();
                    for (auto user : users)
                    {
                        if (user == update.from.id)
                        {
                            is_new_user = false;
                            break;
                        }
                    }
                    if (users.size() < 10 && is_new_user)
                    {
                        sendMessage("You has been saved", update.from.id);
                        db.add_user(update.from.id);
                    }
                    else
                    {
                        if (!is_new_user)
                            sendMessage("You was registered", update.from.id);
                    }
                    break;
                }

                default:
                    break;
                }
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

void TelegramBot::sendMessage(std::string message, int64_t user_id)
{
    try
    {
        this->telegram_client_api_.sendMessage(this->token_, user_id, message);
    }
    catch (const std::exception&)
    {
    }
}

TelegramBot::TelegramMessageCommand TelegramBot::HandlingMessage(const std::string& message)
{
    auto result = TelegramBot::TelegramMessageCommand::Unknown;

    if (message == "Start" || message == "start")
    {
        result = TelegramBot::TelegramMessageCommand::Registration;
    }
    else if (message == "Cancel" || message == "cancel")
    {
        result = TelegramBot::TelegramMessageCommand::CancelRegistration;
    }

    return result;
}

} // namespace telegrambot
