#include "sqlite.hpp"
#include <cstdint>
#include <sqlite3.h>

namespace db::sqlite
{
bool Sqlite::Open(const std::string& path)
{
    if (this->db_)
        return true;

    if (sqlite3_open(path.c_str(), &this->db_) != SQLITE_OK)
    {
        if (this->db_)
        {
            sqlite3_close(this->db_);
            this->db_ = nullptr;
        }
        return false;
    }

    return true;
}

void Sqlite::Close()
{
    if (this->db_)
    {
        sqlite3_close(this->db_);
        this->db_ = nullptr;
    }
}

bool Sqlite::Exec(const std::string& request_sql)
{
    if (!this->db_)
        return false;

    int return_code = sqlite3_exec(this->db_, request_sql.c_str(), nullptr, nullptr, nullptr);
    if (return_code != SQLITE_OK)
        return false;

    return true;
}

bool Sqlite::EnsureTable(const std::string& name, const std::string& schema)
{
    if (!this->db_)
        return false;

    std::string sql_request = "CREATE TABLE IF NOT EXISTS " + name + " (" + schema + ");";

    int return_code = sqlite3_exec(this->db_, sql_request.c_str(), nullptr, nullptr, nullptr);
    if (return_code != SQLITE_OK)
        return false;

    return true;
}

bool Sqlite::HasColumn(const std::string& table, const std::string& column)
{
    if (!this->db_)
        return false;

    std::string sql_request = "PRAGMA table_info(" + table + ");";
    sqlite3_stmt* statement = nullptr;

    int return_code = sqlite3_prepare_v2(this->db_, sql_request.c_str(), -1, &statement, nullptr);
    if (return_code != SQLITE_OK)
        return false;

    bool found = false;

    while (sqlite3_step(statement) == SQLITE_ROW)
    {
        const char* column_name = reinterpret_cast<const char*>(sqlite3_column_text(statement, 1));

        if (column_name && column == column_name)
        {
            found = true;
            break;
        }
    }

    sqlite3_finalize(statement);
    return found;
}

bool Sqlite::AddColumn(const std::string& table, const std::string& column_definition)
{
    if (!this->db_)
        return false;

    std::string sql_request = "ALTER TABLE " + table + " ADD COLUMN " + column_definition + ";";

    int return_code = sqlite3_exec(this->db_, sql_request.c_str(), nullptr, nullptr, nullptr);
    if (return_code != SQLITE_OK)
        return false;

    return true;
}

std::vector<int64_t> Sqlite::GetDataInt64(const std::string& table, const std::string& column)
{
    std::vector<int64_t> result;

    if (!this->db_)
        return result;

    std::string sql_request = "SELECT " + column + " FROM " + table + ";";

    sqlite3_stmt* statement = nullptr;

    if (sqlite3_prepare_v2(this->db_, sql_request.c_str(), -1, &statement, nullptr) != SQLITE_OK)
    {
        return result;
    }

    while (sqlite3_step(statement) == SQLITE_ROW)
    {
        int64_t user_id = sqlite3_column_int64(statement, 0);
        result.push_back(user_id);
    }

    sqlite3_finalize(statement);
    return result;
}
} // namespace db::sqlite
