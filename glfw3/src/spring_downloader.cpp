#include "spring_downloader.h"

#include "../pr-downloader/src/pr-downloader.h"
#include "../pr-downloader/src/FileSystem/FileSystem.h"

SpringDownloader* springDownloader;

void UpdateProgress(int done, int size) {
    springDownloader->downloadProgress(done, size);
}

SpringDownloader::SpringDownloader() :
    #ifdef __linux__
    FOLDER_PATH("./data")
    #elif _WIN32
    FOLDER_PATH("data")
    #endif
{
    MaybeMakeFolder();
    DownloadInit();
    DownloadSetConfig(CONFIG_FILESYSTEM_WRITEPATH, FOLDER_PATH.c_str());
    SetDownloadListener(UpdateProgress);
    springDownloader = this;
}

dlEvent* SpringDownloader::GetEvent() {
    std::unique_lock<std::mutex> lck(dlEventQueueMutex);
    if (!dlEventQueue.empty()) {
        dlEvent* ev = dlEventQueue.front();
		dlEventQueue.pop_front();
        return ev;
    }
    return nullptr;
}

void SpringDownloader::MaybeMakeFolder() {
    if (!CFileSystem::directoryExists(FOLDER_PATH)) {
        CFileSystem::createSubdirs(FOLDER_PATH);
    }
}

int SpringDownloader::DownloadPackage(int count) {
    for (int i = 0; i < count; i++) {
        DownloadAdd(i);
        struct downloadInfo dl;
		if (!DownloadGetInfo(i, dl))
			continue;
    }
    int result;
    if (count == 0) { // there's nothing to download
        result = 2;
        downloadFailed(result);
    } else {
        result = DownloadStart();
        downloadFinished();
        SetAbortDownloads(true);
        SetAbortDownloads(false);
        DownloadShutdown();
        DownloadInit();
        DownloadSetConfig(CONFIG_FILESYSTEM_WRITEPATH, FOLDER_PATH.c_str());
        SetDownloadListener(UpdateProgress);
    }
    return result;
}

int SpringDownloader::DownloadEngine(const std::string& ver_string)
{
    printf("Download engine: %s\n", ver_string.c_str());
    // downloadStarted(ver_string, std::string("Engine"));
    downloadStarted();
    const int count = DownloadSearch(DownloadEnum::CAT_ENGINE,
                                     ver_string.c_str());
    printf("To download; %d\n", count);
    DownloadPackage(count);
}

int SpringDownloader::DownloadGame(const std::string& name)
{
    printf("Download game: %s\n", name.c_str());
    // downloadStarted(name, "Game");
    downloadStarted();
    const int count = DownloadSearch(DownloadEnum::CAT_GAME,
                                     name.c_str());
    printf("To download; %d\n", count);
    DownloadPackage(count);
}

int SpringDownloader::DownloadMap(const std::string& name)
{
    printf("Download map: %s\n", name.c_str());
    // downloadStarted(name, "Map");
    downloadStarted();
    const int count = DownloadSearch(DownloadEnum::CAT_MAP,
                                     name.c_str());
    printf("To download; %d\n", count);
    DownloadPackage(count);
}


void SpringDownloader::downloadStarted()
{
    std::lock_guard<std::mutex> lck(dlEventQueueMutex);
    dlEvent* ev = new dlEvent();
    ev->eventType = dlEvent::EventType::STARTED;
    dlEventQueue.push_back(ev);
}

void SpringDownloader::downloadFinished()
{
    std::lock_guard<std::mutex> lck(dlEventQueueMutex);
    dlEvent* ev = new dlEvent();
    ev->eventType = dlEvent::EventType::FINISHED;
    dlEventQueue.push_back(ev);
}

void SpringDownloader::downloadFailed(int errorID)
{
    std::lock_guard<std::mutex> lck(dlEventQueueMutex);
    dlEvent* ev = new dlEvent();
    ev->eventType = dlEvent::EventType::FAILED;
    ev->errorID = errorID;
    dlEventQueue.push_back(ev);
}

void SpringDownloader::downloadProgress(long downloaded, long total)
{
    std::lock_guard<std::mutex> lck(dlEventQueueMutex);
    dlEvent* ev = new dlEvent();
    ev->eventType = dlEvent::EventType::PROGRESS;
    ev->downloaded = downloaded;
    ev->total = total;
    dlEventQueue.push_back(ev);
}
