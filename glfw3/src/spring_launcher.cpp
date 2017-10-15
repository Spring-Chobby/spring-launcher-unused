#include "spring_launcher.h"

#include <vector>
#include <string>

#include <stdio.h>
#include <string.h>

#ifdef __linux__
#include <unistd.h>
#elif _WIN32
#include <windows.h>
#endif

/**
 * Executes a native binary, file and args have to be not escaped!
 * http://linux.die.net/man/3/execvp
 * @param  file path to an executable, eg. "/usr/bin/games/spring"
 * @param  args arguments to the executable, eg. {"-f". "/tmp/test.txt"}
 * @return error message, or "" on success
 */
std::string ExecuteProcess(const std::string& file, std::vector<std::string> args, bool asSubprocess = false);

void SpringLauncher::Start(const std::string& program, const std::vector<std::string>& args)
{
    ExecuteProcess(program, args);
}


char* safe_strcpy(char* destination, size_t destinationSize, const char* source)
{
	if ((destination != NULL) && (destinationSize > 0)) {
		destination[destinationSize - 1] = '\0';
		destination = strncpy(destination, source, destinationSize - 1);
	}

	return destination;
}

std::string GetShortFileName(const std::string& file) {
    #ifdef WIN32
    std::vector<TCHAR> shortPathC(file.size() + 1, 0);

    // FIXME: stackoverflow.com/questions/843843/getshortpathname-unpredictable-results
    const int length = GetShortPathName(file.c_str(), &shortPathC[0], file.size() + 1);

    if (length > 0 && length <= (file.size() + 1))
        return (std::string(reinterpret_cast<const char*>(&shortPathC[0])));
    #endif

    return file;
}

std::string ExecuteProcess(const std::string& file, std::vector<std::string> args, bool asSubprocess)
{
	// "The first argument, by convention, should point to
	// the filename associated with the file being executed."
	// NOTE:
	//   spaces in the first argument or quoted file paths
	//   are not supported on Windows, so translate <file>
	//   to a short path there
	//args.insert(args.begin(), GetShortFileName(file));
    args.insert(args.begin(), GetShortFileName(file));

	std::string execError;

	// if (asSubprocess) {
	// 	#ifdef WIN32
	// 	STARTUPINFO si;
	// 	PROCESS_INFORMATION pi;
    //
	// 	ZeroMemory(&si, sizeof(si)); si.cb = sizeof(si);
	// 	ZeroMemory(&pi, sizeof(pi));
    //
	// 	std::vector<char> argsVec;
	// 	std::string argsStr;
    //
	// 	for (size_t a = 0; a < args.size(); ++a) {
	// 		argsStr.append(args[a] + ' ');
	// 	}
    //
	// 	argsVec.assign(argsStr.begin(), argsStr.end());
	// 	argsVec.push_back('\0');
    //
	// 	LOG("[%s] Windows start process arguments: %s", __func__, argsStr.c_str());
    //
	// 	if (!CreateProcess(nullptr, argsVec.data(), nullptr, nullptr, TRUE, 0, nullptr, nullptr, &si, &pi))
	// 		LOG("[%s] Error creating subprocess (%lu)", __func__, GetLastError());
    //
	// 	#else
    //
	// 	int pid;
	// 	if ((pid = fork()) < 0) {
	// 		LOG("[%s] Error forking process", __func__);
	// 	} else if (pid != 0) {
	// 		// TODO: Maybe useful to return the subprocess ID (pid)?
	// 	}
	// 	#endif
    //
	// 	return execError;
	// }


	// "The array of pointers must be terminated by a NULL pointer."
	// --> include one extra argument string and leave it NULL
	std::vector<char*> processArgs(args.size() + 1, nullptr);
	for (size_t a = 0; a < args.size(); ++a) {
		const std::string& arg = args[a];
		const size_t argSize = arg.length() + 1;

		safe_strcpy(processArgs[a] = new char[argSize], argSize, arg.c_str());
	}

	#ifdef WIN32
		#define EXECVP _execvp
	#else
		#define EXECVP execvp
	#endif

    if (EXECVP(args[0].c_str(), &processArgs[0]) == -1)
		printf("[%s] error: \"%s\" %s (%d)", __func__, args[0].c_str(), (execError = strerror(errno)).c_str(), errno);

	#undef EXECVP

	for (size_t a = 0; a < args.size(); ++a) {
		delete[] processArgs[a];
	}

	return execError;
}
