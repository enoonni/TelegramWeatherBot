#include "config.hpp"
#include <fstream>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <string>

namespace config
{

Config::Config(const std::string& path)
    : path_(path)
{
}

bool Config::load()
{

    try
    {
        std::ifstream file(this->path_);
        if (!file.is_open())
        {
            return false;
        }

        nlohmann::json json_file;
        file >> json_file;

        if (json_file.contains("token") && json_file["token"].is_string() && !json_file["token"].get<std::string>().empty())
        {
            this->token_ = json_file["token"].get<std::string>();
        }
        else
        {
            this->token_.clear();
            return false;
        }

        return true;
    }
    catch (const std::exception& e)
    {
        this->token_.clear();
        return false;
    }
}

const std::string& Config::GetToken() const
{
    return token_;
}
} // namespace config
