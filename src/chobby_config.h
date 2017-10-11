#ifndef CHOBBYCONFIG_H
#define CHOBBYCONFIG_H

#include <QList>

#include <QString>

class ChobbyConfig
{
private:
    ChobbyConfig(const std::string& fpath);

public:
    static void initialize();

    bool auto_download;
    bool auto_start;
    bool no_downloads;

    QString game_title;
    QString data_folder;

    QList<QString> games;
    QList<QString> maps;
    QList<QString> engines;

    QList<QString> start_args;
};

extern ChobbyConfig* chobbyConfig;

#endif // CHOBBYCONFIG_H
