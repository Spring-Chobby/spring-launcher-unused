#include "chobby_config.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include <iostream>

ChobbyConfig* chobbyConfig;

static QList<QString> ParseJsonArray(const QJsonObject& configObj, const QString& key) {
    QList<QString> strings;
    if (configObj.contains(key)) {
        QJsonArray jsonArray = configObj[key].toArray();
        for (const auto& jsonObj : jsonArray) {
            strings.append(jsonObj.toString());
        }
    }
    return strings;
}

ChobbyConfig::ChobbyConfig(const std::string& fpath)
{
    QFile configFile(fpath.c_str());
    if (!configFile.exists()) {
        std::cerr << "File doesn't exist: " << fpath << std::endl;
    }
    configFile.open(QIODevice::ReadOnly);
    QByteArray configData = configFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(configData));
    QJsonObject configObj = loadDoc.object();

    auto_download = configObj["auto_download"].toBool();
    auto_start = configObj["auto_start"].toBool();
    no_downloads = configObj["no_downloads"].toBool();

    game_title = configObj["game_title"].toString();
    data_folder = configObj["data_folder"].toString();

    games = ParseJsonArray(configObj, "games");
    maps = ParseJsonArray(configObj, "maps");
    engines = ParseJsonArray(configObj, "engines");
    start_args = ParseJsonArray(configObj, "start_args");
}

void ChobbyConfig::initialize()
{
    if (chobbyConfig != nullptr) {
        throw "already initialized";
    }
    chobbyConfig = new ChobbyConfig(":/config/config.json");
    //chobbyConfig = new ChobbyConfig("res/config.json");
    printf("initialized\n");
}
