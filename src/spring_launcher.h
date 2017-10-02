#ifndef SPRINGLAUNCHER_H
#define SPRINGLAUNCHER_H

#include <QObject>

class SpringLauncher : public QObject
{
    Q_OBJECT
public:
    explicit SpringLauncher(QObject *parent = 0);
    void Start();
signals:
    void lobbyClosed();
public slots:
};

#endif // SPRINGLAUNCHER_H
