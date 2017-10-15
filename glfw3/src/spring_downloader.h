#ifndef SPRINGDOWNLOADER_H
#define SPRINGDOWNLOADER_H

#include <string>
#include <mutex>
#include <deque>

struct dlEvent {
    enum class EventType { STARTED, FINISHED, FAILED, PROGRESS };
    EventType eventType;

    int errorID; // only for FAILED

    long downloaded; // only for PROGRESS
    long total; // only for PROGRESS
};

class SpringDownloader
{
public:
    explicit SpringDownloader();

    int DownloadEngine(const std::string& ver_string);
    int DownloadGame(const std::string& name);
    int DownloadMap(const std::string& name);

    std::string FOLDER_PATH;

    dlEvent* GetEvent();

    void downloadProgress(long downloaded, long total);

private:
    void MaybeMakeFolder();
    int DownloadPackage(int count);

    void downloadStarted();
    void downloadFinished();
    void downloadFailed(int errorID);

    std::deque<dlEvent*> dlEventQueue;
    std::mutex dlEventQueueMutex;
};

extern SpringDownloader* springDownloader;

#endif // SPRINGDOWNLOADER_H
