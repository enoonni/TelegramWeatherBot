#include "telegram_client_api.hpp"
#include "http_client.hpp"
#include "message_context.hpp"

#include <nlohmann/json.hpp>
#include <stdexcept>

namespace telegram_bot::telegram_client_api
{

std::vector<telegram_bot::dto::MessageContext> TelegramClientApi::Update(std::string token)
{
    const std::string url = "https://api.telegram.org/bot" + token + "/getUpdates";
    http::HttpClient client;

    auto response = client.get(url, {{"Accept", "application/json"}});
    if (response.status != 200)
        throw std::runtime_error("Telegram API error!");

    nlohmann::json json = nlohmann::json::parse(response.body);

    if (!json.contains("ok") || !json["ok"].get<bool>())
        throw std::runtime_error("Telegram API json returned ok=false");

    std::vector<telegram_bot::dto::MessageContext> updates;

    for (const auto& update : json["result"])
    {
        if (!update.contains("message"))
            continue;

        const auto& message = update["message"];

        telegram_bot::dto::MessageContext context;
        context.update_id = update["update_id"];
        context.message_id = update["message_id"];
        context.timestamp = update["date"];

        const auto& from = message["from"];
        context.from.id = from["id"];
        context.from.is_bot = from.value("is_bot", false);
        context.from.first_name = from.value("first_name", "");
        context.from.last_name = from.value("last_name", "");
        context.from.username = from.value("username", "");

        const auto& chat = message["chat"];
        context.chat.id = chat["id"];
        context.chat.is_private = chat["type"] == "private";
        context.chat.title = chat.value("title", "");

        if (message.contains("text"))
        {
            context.text = message["text"];

            if (!context.text.empty() && context.text[0] == '/')
                context.type = dto::MessageType::Command;
            else
                context.type = dto::MessageType::Text;
        }
        else
        {
            context.type = dto::MessageType::Unknown;
        }

        updates.push_back(std::move(context));
    }

    return updates;
}

}; // namespace telegram_bot::telegram_client_api
