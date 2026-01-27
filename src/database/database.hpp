#pragma once
#include <string>
#include <vector>

namespace db
{
class Database
{
  public:
    bool Initialize(std::string path);
    void AddUser(int64_t user_id);
    void AddUsers(std::vector<int64_t>);
    std::vector<int64_t> GetUsers();

  private:
    std::string path_;
};
} // namespace db
