#include "database.hpp"
#include "sqlite/sqlite.hpp"
#include <cstdint>
#include <iostream>
#include <sqlite3.h>
#include <string>
#include <vector>

namespace db
{

bool Database::initialize()
{
    try
    {
        sqlite::Sqlite sqlite;

        if (!sqlite.open(this->path_))
            return false;

        if (!sqlite.ensure_table(this->user_table_name_, this->user_table_schema))
        {
            sqlite.close();
            return false;
        }

        if (!sqlite.has_column(this->user_table_name_, this->user_id_column_name_))
        {
            if (!sqlite.add_column(this->user_table_name_, this->user_id_column_name_ + " INTEGER NOT NULL UNIQUE"))
            {
                sqlite.close();
                return false;
            }
        }
        sqlite.close();
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Database init error: " << e.what() << "\n";
        return false;
    }
}

void Database::add_user(int64_t user_id)
{
    sqlite::Sqlite sqlite;

    if (!sqlite.open(this->path_))
    {
        sqlite.close();
        return;
    }

    std::string sql_request = "INSERT OR IGNORE INTO " + this->user_table_name_ + " (" + this->user_id_column_name_ + ") VALUES (" + std::to_string(user_id) + ");";

    sqlite.exec(sql_request);
    sqlite.close();
}

void Database::add_users(std::vector<int64_t> users_id)
{
    sqlite::Sqlite sqlite;

    if (!sqlite.open(this->path_) || users_id.size() == 0)
    {
        sqlite.close();
        return;
    }

    std::string sql_request = "INSERT OR IGNORE INTO " + this->user_table_name_ + " (" + this->user_id_column_name_ + ") VALUES ";

    for (size_t i = 0; i < users_id.size(); ++i)
    {
        sql_request += ("(" + std::to_string(users_id[i]) + ")");
        if (i + 1 < users_id.size())
            sql_request += ",";
    }
    sql_request += ";";
    sqlite.exec(sql_request);

    sqlite.close();
}

std::vector<int64_t> Database::get_users()
{
    std::vector<int64_t> result;
    sqlite::Sqlite sqlite;

    if (!sqlite.open(this->path_))
    {
        sqlite.close();
        return result;
    }

    result = sqlite.get_data_int64(this->user_table_name_, this->user_id_column_name_);

    sqlite.close();
    return result;
}

} // namespace db
