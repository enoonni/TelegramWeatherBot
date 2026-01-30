#pragma once

#include <sqlite3.h>
#include <string>
#include <vector>
namespace db::sqlite
{
class Sqlite
{
  public:
    bool open(const std::string& path);
    void close();
    bool exec(const std::string& request_sql);
    bool ensure_table(const std::string& name, const std::string& schema);
    bool has_column(const std::string& table, const std::string& column);
    bool add_column(const std::string& table, const std::string& column_definition);
    std::vector<int64_t> get_data_int64(const std::string& table, const std::string& column);

  private:
    sqlite3* db_ = nullptr;
};
} // namespace db::sqlite
