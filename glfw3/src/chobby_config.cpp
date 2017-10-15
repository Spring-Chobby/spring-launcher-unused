#include "chobby_config.h"

#include <iostream>
#include <fstream>

#include "../pr-downloader/src/lib/jsoncpp/include/json/reader.h"

ChobbyConfig* chobbyConfig;

static std::list<std::string> ParseJsonArray(const Json::Value& configObj, const std::string& key) {
    std::list<std::string> strings;
    if (configObj.isMember(key)) {
        const Json::Value& value = configObj[key];
        for (const auto& jsonObj : value) {
            strings.push_back(jsonObj.asString());
            printf("KEY: %s VALUE: %s\n", key.c_str(), jsonObj.asString().c_str());
        }
    }
    return strings;
}

ChobbyConfig::ChobbyConfig(const std::string& fpath)
{
    std::ifstream configFile;
    configFile.open(fpath, std::ios::out | std::ios::binary);
    if (!configFile.is_open()) {
        std::cerr << "File doesn't exist: " << fpath << std::endl;
        return;
    }
    const std::string str((std::istreambuf_iterator<char>(configFile)),
                     std::istreambuf_iterator<char>());
    configFile.close();

    Json::Reader reader;
    Json::Value configObj;
    const bool success = reader.parse(str, configObj);
    if (!success) {
        std::cerr << "Failed to parse json file: " << fpath << std::endl;
    }

    auto_download = configObj["auto_download"].asBool();
    auto_start = configObj["auto_start"].asBool();
    no_downloads = configObj["no_downloads"].asBool();
    game_title = configObj["game_title"].asString();

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
    chobbyConfig = new ChobbyConfig("./res/config.json");
    printf("initialized\n");
}
