# TelegramWeatherBot

A C++ systemd daemon that sends weather updates for Stavropol via Telegram.

## Prerequisites

Ensure you have the following dependencies installed:

* **Compiler**: GCC or Clang with C++17 support.
* **Build System**: CMake (>= 3.10) and Ninja.
* **Libraries**: 
    * `libcurl`
    * `nlohmann_json`
    * `sqlite3`


Building

This project uses CMake with the Ninja generator.

1. Configure the project:

  cmake -S . -B build -G Ninja

2. Build the binary:

  cmake --build build

3. Install: The default installation prefix is /opt/telegram-weather-bot.

  sudo cmake --install build --prefix /opt/telegram-weather-bot

Configuration & Environment Setup
1. Create Required Directories

The bot requires a state directory for the database and a configuration directory. Replace YOUR_USER with your actual Linux username.
# State directory (Database)
    sudo mkdir -p /var/lib/telegram-weather-bot
    sudo chown YOUR_USER:YOUR_USER /var/lib/telegram-weather-bot

# Configuration directory
    sudo mkdir -p /etc/telegram-weather-bot

2. Configure the Bot

Create the configuration file at /etc/telegram-weather-bot/bot_config.json:
  {
    "token": "YOUR_TELEGRAM_BOT_TOKEN"
  }

Set permissions (secure the token):
  sudo chown YOUR_USER:YOUR_USER /etc/telegram-weather-bot/bot_config.json
  sudo chmod 600 /etc/telegram-weather-bot/bot_config.json


Systemd Integration
1. Create the Service Unit

Create a file at /etc/systemd/system/telegram-weather-bot.service with the following content:

    [Unit]
    Description=Telegram Weather Bot
    After=network-online.target
    Wants=network-online.target

    [Service]
    Type=simple
    ExecStart=/opt/telegram-weather-bot/bin/TelegramWeatherBot
    WorkingDirectory=/var/lib/telegram-weather-bot

    User=YOUR_USER
    Group=YOUR_USER

    Restart=on-failure
    RestartSec=5

# Sandboxing & Security
    NoNewPrivileges=true
    PrivateTmp=true
    ProtectSystem=full
    ProtectHome=true
    ReadWritePaths=/var/lib/telegram-weather-bot
    ReadOnlyPaths=/etc/telegram-weather-bot

    StandardOutput=journal
    StandardError=journal

    [Install]
    WantedBy=multi-user.target

2. Manage the Daemon
# Reload systemd to recognize the new unit
    sudo systemctl daemon-reload

# Enable and start the bot
    sudo systemctl enable telegram-weather-bot.service
    sudo systemctl start telegram-weather-bot.service

# Monitor logs
    journalctl -u telegram-weather-bot.service -f
