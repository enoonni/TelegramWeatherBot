#pragma once
#include <string>
#include <vector>

namespace db
{
class Database
{
  public:
    bool initialize();
    void add_user(int64_t user_id);
    void add_users(std::vector<int64_t> users_id);
    std::vector<int64_t> get_users();

  private:
    const std::string path_ = "/var/lib/telegram-weather-bot/users.db";
    const std::string user_table_name_ = "telegram_users";
    const std::string user_id_column_name_ = "user_id";
    const std::string user_table_schema = "id INTEGER PRIMARY KEY AUTOINCREMENT, user_id INTEGER UNIQUE NOT NULL";
};
} // namespace db
