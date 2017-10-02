#ifndef SPRINGDOWNLOADER_H
#define SPRINGDOWNLOADER_H

#include <QObject>

class SpringDownloader : public QObject
{
    Q_OBJECT

public:
    explicit SpringDownloader(QObject *parent = 0);

    int DownloadEngine(const QString& ver_string);
    int DownloadGame(const QString& name);
    int DownloadMap(const QString& name);

    QString FOLDER_PATH;
private:

    void MaybeMakeFolder();
    int DownloadPackage(int count);

signals:
    void downloadStarted(const QString& name, const QString& type);
    void downloadFinished();
    void downloadFailed(const QString& msg);
    void downloadProgress(int current, int total);

public slots:
};

extern SpringDownloader* springDownloader;

#endif // SPRINGDOWNLOADER_H
