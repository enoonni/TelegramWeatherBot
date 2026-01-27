#pragma once

#include <sqlite3.h>
#include <string>
namespace db::sqlite
{
class Sqlite
{
  public:
    bool Open(const std::string& path);
    void Close();
    bool Exec(const std::string& request_sql);
    bool EnsureTable(const std::string& name, const std::string& schema);
    bool HasColumn(const std::string& table, const std::string& column);
    bool AddColumn(const std::string& table, const std::string& column_definition);

  private:
    sqlite3* db_ = nullptr;
};
} // namespace db::sqlite
