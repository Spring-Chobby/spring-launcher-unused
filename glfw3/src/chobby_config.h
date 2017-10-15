#ifndef CHOBBYCONFIG_H
#define CHOBBYCONFIG_H

#include <string>
#include <list>

class ChobbyConfig
{
private:
    ChobbyConfig(const std::string& fpath);

public:
    static void initialize();

    bool auto_download;
    bool auto_start;
    bool no_downloads;

    std::string game_title;

    std::list<std::string> games;
    std::list<std::string> maps;
    std::list<std::string> engines;

    std::list<std::string> start_args;
};

extern ChobbyConfig* chobbyConfig;

#endif // CHOBBYCONFIG_H
