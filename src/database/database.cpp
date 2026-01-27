#include "database.hpp"
#include "sqlite/sqlite.hpp"
#include <filesystem>
#include <sqlite3.h>

namespace db
{
bool Database::Initialize(std::string path)
{
    this->path_ = path;

    sqlite3* db = nullptr;

    int rc = sqlite3_open(this->path_.c_str(), &db);
    if (rc != SQLITE_OK || !db)
    {
        if (db)
            sqlite3_close(db);

        return false;
    }

    const char* check_and_create_table_request = R"(CREATE TABLE IF NOT EXISTS telegram_users(
                                                      id INTEGER PRIMARY KEY AUTOINCREMENT,
                                                      user_id INTEGER NOT NULL UNIQUE
                                                    );
                                                  )";

    rc = sqlite3_exec(db, check_and_create_table_request, nullptr, nullptr, nullptr);
    if (rc != SQLITE_OK)
    {
        sqlite3_close(db);
        return false;
    }

    const char* pragma_sql = "PRAGMA table_info(telegram_users);";
    sqlite3_stmt* stmt = nullptr;

    rc = sqlite3_prepare_v2(db, pragma_sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        sqlite3_close(db);
    }

    bool has_user_id = false;
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        const char* col_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));

        if (col_name && std::string(col_name) == "user_id")
        {
            has_user_id = true;
            break;
        }
    }

    sqlite3_finalize(stmt);

    if (!has_user_id)
    {
        const char* alter_request = "ALTER TABLE telegram_users ADD COLUMN user_id INTEGER NOT NULL UNIQUE;";
        rc = sqlite3_exec(db, alter_request, nullptr, nullptr, nullptr);
        if (rc != SQLITE_OK)
        {
            sqlite3_close(db);
            return false;
        }
    }

    sqlite3_close(db);
    return true;
}

} // namespace db
