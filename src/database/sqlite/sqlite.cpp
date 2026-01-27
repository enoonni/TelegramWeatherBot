#include "sqlite.hpp"
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
}

bool Sqlite::EnsureTable(const std::string& name, const std::string& schema)
{
}

bool Sqlite::HasColumn(const std::string& table, const std::string& column)
{
}

bool Sqlite::AddColumn(const std::string& table, const std::string& column_definition)
{
}
} // namespace db::sqlite
