#pragma once
#include <string>
namespace config
{
class Config
{
  public:
    Config(const std::string& path);
    bool load();
    const std::string& GetToken() const;

  private:
    std::string path_;
    std::string token_;
};
} // namespace config
