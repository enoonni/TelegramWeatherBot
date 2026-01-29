#pragma once
#include <string>
#include <vector>

namespace db
{
class Database
{
  public:
    bool Initialize(const std::string& path);
    void AddUser(int64_t user_id);
    void AddUsers(std::vector<int64_t> users_id);
    std::vector<int64_t> GetUsers();

  private:
    std::string path_;
    const std::string user_table_name_ = "telegram_users";
    const std::string user_id_column_name_ = "user_id";
    const std::string user_table_schema = "id INTEGER PRIMARY KEY AUTOINCREMENT, user_id INTEGER UNIQUE NOT NULL";
};
} // namespace db
