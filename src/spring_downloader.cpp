#include "spring_downloader.h"

#include "../pr-downloader/src/pr-downloader.h"

#include <QDir>

SpringDownloader* springDownloader;

void UpdateProgress(int done, int size) {
    emit springDownloader->downloadProgress(done, size);
}

SpringDownloader::SpringDownloader(QObject *parent) :
    QObject(parent), FOLDER_PATH(QDir::currentPath() + "/data")
{
    MaybeMakeFolder();
    DownloadSetConfig(CONFIG_FILESYSTEM_WRITEPATH, FOLDER_PATH.toStdString().c_str());
    SetDownloadListener(UpdateProgress);
}

void SpringDownloader::MaybeMakeFolder() {
    if (!QDir(FOLDER_PATH).exists()) {
        QDir().mkdir(FOLDER_PATH);
    }
}

int SpringDownloader::DownloadPackage(int count) {
    for (int i = 0; i < count; i++) {
        DownloadAdd(i);
    }
    int result;
    if (count == 0) { // there's nothing to download
        result = 2;
        emit downloadFailed("Nothing to download.");
    } else {
        result = DownloadStart();
        emit downloadFinished();
    }
    return result;
}

int SpringDownloader::DownloadEngine(const QString& ver_string)
{
    emit downloadStarted(ver_string, QString("Engine"));
    const int count = DownloadSearch(DownloadEnum::CAT_ENGINE,
                                     ver_string.toStdString().c_str());
    DownloadPackage(count);
}

int SpringDownloader::DownloadGame(const QString& name)
{
    emit downloadStarted(name, "Game");
    const int count = DownloadSearch(DownloadEnum::CAT_GAME,
                                     name.toStdString().c_str());
    DownloadPackage(count);
}

int SpringDownloader::DownloadMap(const QString& name)
{
    emit downloadStarted(name, "Map");
    const int count = DownloadSearch(DownloadEnum::CAT_MAP,
                                     name.toStdString().c_str());
    DownloadPackage(count);
}
