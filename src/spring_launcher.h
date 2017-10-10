#ifndef SPRINGLAUNCHER_H
#define SPRINGLAUNCHER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QProcess>

class SpringLauncher : public QObject
{
    Q_OBJECT
public:
    explicit SpringLauncher(QObject *parent = 0);
    void Start(const QString& program, const QStringList& args);
    #ifdef __linux__
        QString SPRING_EXE = "spring";
    #elif _WIN32
        QString SPRING_EXE = "spring.exe";
    #endif
private:
    QProcess *myProcess;
    void Finished(int exitCode, QProcess::ExitStatus exitStatus);
signals:
    void lobbyClosed();
public slots:
};

#endif // SPRINGLAUNCHER_H
