#ifndef SPRINGLAUNCHER_H
#define SPRINGLAUNCHER_H

#include <string>
#include <vector>

class SpringLauncher
{
public:
    #ifdef __linux__
        std::string SPRING_EXE = "spring";
    #elif _WIN32
        std::string SPRING_EXE = "spring.exe";
    #endif

    void Start(const std::string& program, const std::vector<std::string>& args);
    void lobbyClosed();
};

#endif // SPRINGLAUNCHER_H
