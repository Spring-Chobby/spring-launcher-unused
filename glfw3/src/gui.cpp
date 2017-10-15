#include <thread>

#ifdef __linux__
#include <unistd.h>
#elif _WIN32
#include <windows.h>
#endif

#include <string>
#include <iostream>

#include <nanogui/screen.h>
#include <nanogui/window.h>
#include <nanogui/layout.h>
#include <nanogui/button.h>
#include <nanogui/glutil.h>
#include <nanogui/label.h>
#include <nanogui/theme.h>
#include <nanogui/formhelper.h>
#include <nanogui/nanogui.h>

#include "gui.h"
#include "chobby_config.h"

using nanogui::Screen;
using nanogui::Window;
using nanogui::GridLayout;
using nanogui::ProgressBar;
using nanogui::Button;
using nanogui::Label;
using nanogui::Vector2i;

GUI::GUI() {
    downloader = new SpringDownloader();
    launcher = new SpringLauncher();

    games = chobbyConfig->games;
    maps = chobbyConfig->maps;
    engines = chobbyConfig->engines;
    t = nullptr;
}

GUI::~GUI() {
    delete downloader;
    delete launcher;
}

void GUI::Loop() {
    nanogui::init();
    /**
     * Create a screen, add a window.
     * To the window add a label and a slider widget.
     */

    Screen app{{400, 300}, chobbyConfig->game_title.c_str()};

    Window window{&app, ""};
    window.setPosition({0, 0});
    //window.setLayout(new GridLayout());

    lblStatus = new Label(&window, "Initializing...", "sans-bold");
    lblStatus->setFontSize(20);
    lblStatus->setPosition({50, 150});
    lblStatus->setSize({340, 30});
    lblStatus->setVisible(true);
    mProgress = new ProgressBar(&window);
    mProgress->setValue(0.0);
    mProgress->setPosition({50, 220});
    mProgress->setSize({200, 30});

    // Do the layout calculations based on what was added to the GUI
    //app.performLayout();
    window.setSize({400, 300});

    app.drawAll();
    app.setVisible(true);
    NextStep();
    while (!glfwWindowShouldClose(app.glfwWindow()))
    {
        /* Render here */
        ProcessEvents();

        glClearColor(0,0,0,1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        app.drawWidgets();

        glfwSwapBuffers(app.glfwWindow());
        glfwPollEvents();

        //mySleep(50);
    }



    nanogui::shutdown();
    exit(EXIT_SUCCESS);
}


std::string ExePath() {
    char buffer[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH );
    std::string::size_type pos = std::string( buffer ).find_last_of( "\\/" );
    return std::string( buffer ).substr( 0, pos);
}

std::string GetFullPath(const std::string& file) {
    #ifdef _WIN32
    std::vector<TCHAR> fullPath(4096, 0);
    TCHAR** lppPart={NULL};
    const int length = GetFullPathName(file.c_str(), 4096, &fullPath[0], lppPart);

    printf("TRYING TO GET WINDOWS FULL PATH\n");

    if (length > 0 && length <= (file.size() + 1))
        return (std::string(reinterpret_cast<const char*>(&fullPath[0])));
    #endif

    return file;
}

void GUI::NextStep() {
    if (t != nullptr) {
        t->join();
        delete t;
        t = nullptr;
    }
    if (steps.empty()) {
        return;
    }
    currentStep = steps.front();
    if (currentStep == "autoupdate") {
        steps.pop_front();
        printf("Autoupdate...\n");
        NextStep();
    } else if (currentStep == "packages") {
        printf("Packages\n");
        //printf("this %d %d %d\n", games.size(), maps.size(), engines.size());
        if (!games.empty()) {
            std::string game = this->games.front();
            t = new std::thread( [=] {
                lblStatus->setCaption("Downloading game: " + game);
                downloader->DownloadGame(game);
                printf("Downloaded %s\n", game.c_str());
            } );
            games.pop_front();
        } else if (!maps.empty()) {
            std::string map = maps.front();
            t = new std::thread( [=] {
                lblStatus->setCaption("Downloading map: " + map);
                downloader->DownloadMap(map);
            } );
            maps.pop_front();
        } else if (!engines.empty()) {
            std::string engine = engines.front();
            t = new std::thread( [=] {
                lblStatus->setCaption("Downloading engine: " + engine);
                downloader->DownloadEngine(engine);
            } );
            engines.pop_front();
        } else {
            steps.pop_front();
            if (!chobbyConfig->auto_start) {
                //ui->btnAction->setEnabled(true);
            } else {
                NextStep();
            }
        }
    } else if (currentStep == "launch") {
        steps.pop_front();
        lblStatus->setCaption("Launching");
        #ifdef __linux__
        const std::string program = downloader->FOLDER_PATH + "/engine/" + chobbyConfig->engines.front() + "/" + launcher->SPRING_EXE;
        #elif _WIN32
        const std::string program = downloader->FOLDER_PATH + "\\engine\\" + chobbyConfig->engines.front() + "\\" + launcher->SPRING_EXE;
        #endif
        printf("Launching: %s\n", program.c_str());
        std::vector<std::string> args;
        for (auto& arg : chobbyConfig->start_args) {
            args.push_back(arg);
        }
        args.push_back("--write-dir");
        #ifdef __linux__
            const std::string DATADIR = downloader->FOLDER_PATH;
        #elif _WIN32
            const std::string DATADIR = ExePath() + "\\" + downloader->FOLDER_PATH;
        #endif
        printf("DATADIR: %s\n", DATADIR.c_str());
        args.push_back(DATADIR);
        launcher->Start(program, args);
        //NextStep();
    }
}

void GUI::ProcessEvents() {
    dlEvent* event = downloader->GetEvent();
    if (event != nullptr) {
        switch (event->eventType) {
            case dlEvent::EventType::STARTED:
            OnDownloadStarted();
            break;

            case dlEvent::EventType::FINISHED:
            OnDownloadFinished();
            break;

            case dlEvent::EventType::FAILED:
            OnDownloadFailed(event->errorID);
            break;

            case dlEvent::EventType::PROGRESS:
            OnDownloadProgress(event->downloaded, event->total);
            break;
        }

        delete event;
    }
}
void GUI::OnDownloadStarted()
{

}

void GUI::OnDownloadFinished()
{
    NextStep();
    // SetStep(Step::AUTOUPDATE);
    // NextStep();
}

void GUI::OnDownloadFailed(int errorID)
{
    NextStep();
}

void GUI::OnDownloadProgress(long current, long total)
{
    mProgress->setValue(current * 1.0 / total);
}
