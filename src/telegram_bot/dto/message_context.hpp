#pragma once
#include <cstdint>
#include <string>

namespace telegrambot::dto
{
struct User
{
    int64_t id;
    std::string username;
    std::string first_name;
    std::string last_name;
    bool is_bot = false;
};

struct Chat
{
    int64_t id;
    bool is_private = true;
    std::string title;
};

enum class MessageType
{
    Text,
    Command,
    Photo,
    Callback,
    Unknown
};

struct MessageContext
{
    int64_t update_id;
    int64_t message_id;
    Chat chat;
    User from;

    MessageType type = MessageType::Unknown;
    std::string text;
    std::string payload;
    int64_t timestamp;
};
} // namespace telegrambot::dto
