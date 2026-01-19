# TelegramWeatherBot

sudo cmake --install build --prefix /opt/telegram-weather-bot

/etc/systemd/system/telegram-weather-bot.service
[Unit]
Description=Telegram Weather Bot
After=network-online.target
Wants=network-online.target

[Service]
Type=simple
ExecStart=/opt/telegram-weather-bot/bin/TelegramWeatherBot
WorkingDirectory=/opt/telegram-weather-bot

User=enoonni
Group=enoonni

Restart=on-failure
RestartSec=5

StandardOutput=journal
StandardError=journal

[Install]
WantedBy=multi-user.target
