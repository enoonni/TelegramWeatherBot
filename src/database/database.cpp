#include "database.hpp"
#include "sqlite/sqlite.hpp"
#include <cstdint>
#include <sqlite3.h>
#include <string>
#include <vector>

namespace db
{

bool Database::Initialize(const std::string& path)
{
    this->path_ = path;
    sqlite::Sqlite sqlite;

    if (!sqlite.Open(this->path_))
        return false;

    if (!sqlite.EnsureTable(this->user_table_name_, this->user_table_schema))
    {
        sqlite.Close();
        return false;
    }

    if (!sqlite.HasColumn(this->user_table_name_, this->user_id_column_name_))
    {
        if (!sqlite.AddColumn(this->user_table_name_, this->user_id_column_name_ + " INTEGER NOT NULL UNIQUE"))
        {
            sqlite.Close();
            return false;
        }
    }
    sqlite.Close();
    return true;
}

void Database::AddUser(int64_t user_id)
{
    sqlite::Sqlite sqlite;

    if (!sqlite.Open(this->path_))
    {
        sqlite.Close();
        return;
    }

    std::string sql_request = "INSERT OR IGNORE INTO " + this->user_table_name_ + " (" + this->user_id_column_name_ + ") VALUES (" + std::to_string(user_id) + ");";

    sqlite.Exec(sql_request);
    sqlite.Close();
}

void Database::AddUsers(std::vector<int64_t> users_id)
{
    sqlite::Sqlite sqlite;

    if (!sqlite.Open(this->path_) || users_id.size() == 0)
    {
        sqlite.Close();
        return;
    }

    std::string sql_request = "INSERT OR IGNORE INTO " + this->user_table_name_ + " (" + this->user_id_column_name_ + ") VALUES ";

    for (size_t i = 0; i < users_id.size(); ++i)
    {
        sql_request += ("(" + std::to_string(users_id[i]) + ")");
        if (i < users_id.size())
            sql_request += ",";
    }
    sql_request += ";";
    sqlite.Exec(sql_request);

    sqlite.Close();
}

std::vector<int64_t> Database::GetUsers()
{
    std::vector<int64_t> result;
    sqlite::Sqlite sqlite;

    if (!sqlite.Open(this->path_))
    {
        sqlite.Close();
        return result;
    }

    result = sqlite.GetDataInt64(this->user_table_name_, this->user_id_column_name_);

    sqlite.Close();
    return result;
}

} // namespace db
