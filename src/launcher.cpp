#include "launcher.h"
#include "ui_launcher.h"

#include "chobby_config.h"

#include <QAbstractButton>
#include <QDir>

#include <stdio.h>

#include "spring_downloader.h"

Launcher::Launcher(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::Launcher)
{
    ui->setupUi(this);
    QObject::connect(ui->btnAction, &QAbstractButton::clicked,
                     this,          &Launcher::OnBtnActionClicked);

    ui->lblTitle->setText(chobbyConfig->game_title);
    ui->lblTitle->adjustSize();

    games = chobbyConfig->games;
    maps = chobbyConfig->maps;
    engines = chobbyConfig->engines;

    springDownloader = new SpringDownloader();
    connect(springDownloader,  &SpringDownloader::downloadStarted,
            this,              &Launcher::OnDownloadStarted);
    connect(springDownloader,  &SpringDownloader::downloadFinished,
            this,              &Launcher::OnDownloadFinished);
    connect(springDownloader,  &SpringDownloader::downloadFailed,
            this,              &Launcher::OnDownloadFailed);
    connect(springDownloader,  &SpringDownloader::downloadProgress,
            this,              &Launcher::OnDownloadProgress);

    connect(this,              &Launcher::DownloadGame,
            springDownloader,  &SpringDownloader::DownloadGame);
    connect(this,              &Launcher::DownloadMap,
            springDownloader,  &SpringDownloader::DownloadMap);
    connect(this,              &Launcher::DownloadEngine,
            springDownloader,  &SpringDownloader::DownloadEngine);

    springDownloader->moveToThread(&workerThread);
    workerThread.start();

    springLauncher = new SpringLauncher();
    connect(springLauncher,  &SpringLauncher::lobbyClosed,
            this,            &Launcher::OnLobbyClosed);

    currentStep = Step::START;
    NextStep();
}

Launcher::~Launcher()
{
    delete ui;
}

void Launcher::SetStep(const Step& step) {
    printf("Set state: %d\n", step);
    currentStep = step;
}

void Launcher::NextStep() {
    switch (currentStep) {
        case Step::START:
            SetStep(Step::AUTOUPDATE);
            ui->btnAction->setText("Auto-update");
            ui->btnAction->setEnabled(false);
            NextStep();
        break;

        case Step::AUTOUPDATE:
            SetStep(Step::PACKAGES);
            ui->btnAction->setText("Download");

            if (!games.empty()) {
                QString game = games.front();
                DownloadGame(game);
                games.removeFirst();
            } else if (!maps.empty()) {
                QString map = maps.front();
                DownloadMap(map);
                maps.removeFirst();
            } else if (!engines.empty()) {
                QString engine = engines.front();
                engines.removeFirst();
                if (!QDir(springDownloader->FOLDER_PATH + "/engine/" + engine).exists()) {
                    DownloadEngine(engine);
                } else {
                    printf("Engine %s already exists.\n", engine.toStdString().c_str());
                    NextStep();
                }
            } else {
                if (!chobbyConfig->auto_start) {
                    ui->btnAction->setEnabled(true);
                } else {
                    NextStep();
                }
            }
        break;

        case Step::PACKAGES:
            SetStep(Step::LAUNCH);
            ui->btnAction->setText("Launch");
            QString program = springDownloader->FOLDER_PATH + "/engine/" + chobbyConfig->engines.front() + "/" + springLauncher->SPRING_EXE;
            QStringList arguments;
            for (const QString& arg : chobbyConfig->start_args) {
                arguments << arg;
            }
            springLauncher->Start(program, arguments);
            this->hide();
        break;
    }
}

void Launcher::OnDownloadStarted(const QString& name, const QString& type)
{
    ui->lblStatus->setText("Downloading: " + name);
    ui->lblStatus->adjustSize();
}

void Launcher::OnDownloadFinished()
{
    ui->lblStatus->setText("Download finished.");
    ui->lblStatus->adjustSize();
    SetStep(Step::AUTOUPDATE);
    NextStep();
}

void Launcher::OnDownloadFailed(const QString& msg)
{
    ui->lblStatus->setText(msg);
    ui->lblStatus->adjustSize();
}

void Launcher::OnDownloadProgress(int current, int total)
{
    ui->prDownload->setValue(current * 100.0 / total);
}

void Launcher::OnLobbyClosed()
{
    QApplication::quit();
}

void Launcher::OnBtnActionClicked()
{
    printf("clicked\n");
}
