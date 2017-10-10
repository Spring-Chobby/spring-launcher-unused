#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QMainWindow>
#include <QThread>

#include "spring_downloader.h"
#include "spring_launcher.h"

namespace Ui {
class Launcher;
}

class Launcher : public QMainWindow
{
    Q_OBJECT
    QThread workerThread;
public:
    explicit Launcher(QWidget *parent = 0);
    ~Launcher();

private slots:
    void OnBtnActionClicked();

    void OnDownloadStarted(const QString& name, const QString& type);
    void OnDownloadFinished();
    void OnDownloadFailed(const QString& msg);
    void OnDownloadProgress(int current, int total);

    void OnLobbyClosed();

signals:
    void DownloadEngine(const QString& ver_string);
    void DownloadGame(const QString& name);
    void DownloadMap(const QString& name);

private:
    Ui::Launcher *ui;

    QList<QString> games;
    QList<QString> maps;
    QList<QString> engines;

    enum class Step { START, AUTOUPDATE, PACKAGES, LAUNCH };
    void SetStep(const Step& step);
    Step currentStep;
    void NextStep();

    SpringLauncher* springLauncher;
};

#endif // LAUNCHER_H
