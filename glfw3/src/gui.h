#ifndef GUI_H
#define GUI_H

#include <string>
#include <list>
#include <thread>

#include <nanogui/progressbar.h>

#include "spring_downloader.h"
#include "spring_launcher.h"

class GUI {
public:
    GUI();
    ~GUI();
    void Loop();
private:
    void ProcessEvents();
    void OnDownloadStarted();
    void OnDownloadFinished();
    void OnDownloadFailed(int errorID);
    void OnDownloadProgress(long current, long total);

    SpringDownloader* downloader;
    SpringLauncher* launcher;

    std::list<std::string> games;
    std::list<std::string> maps;
    std::list<std::string> engines;

    std::list<std::string> steps = { "autoupdate", "packages", "launch" };
    std::string currentStep;
    // Step currentStep;
    // void SetStep(const std::string& step);
    void NextStep();

    std::thread* t;

    nanogui::ProgressBar *mProgress;
    nanogui::Label *lblStatus;
};

#endif // GUI_H
