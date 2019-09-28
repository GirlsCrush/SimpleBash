#include <string>
#include <iostream>
#include <fstream>
#include <regex>
#include <algorithm>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include "Keys.h"

static std::string buf;
static Keys keys;

void getCmd() {
    keys.clearKeys();
    std::smatch result;
    std::regex reg("([\\w]+)[ ]?([- \\w\\d]*)");
    std::regex regKeys("([-\\w\\d]+)");
    std::regex_search(buf, result, reg);
   
    keys.addKey(result[1].str());
    std::string keysStr = result[2].str();
    buf = result.suffix().str();
    
    while (std::regex_search(keysStr, result, regKeys)) {
        keys.addKey(result[1].str());
        keysStr = result.suffix().str();
    }
}

int main() {

    std::getline(std::cin, buf);
    int pid;
    int pfd[2];
    while (buf != "") {
        pipe(pfd);
        getCmd();
        if (pid = fork()) {
			close(STDOUT_FILENO);
        	dup2(pfd[1], STDOUT_FILENO);
        	close(pfd[1]);
        	close(pfd[0]);
        	execvp(keys.getCmd(), keys.keys);
		} else {
            sleep(1);
			close(STDIN_FILENO);
        	dup2(pfd[0], STDIN_FILENO);
        	close(pfd[1]);
        	close(pfd[0]);
		}
    }

    std::ofstream ofs("result.out");
    // std::ofstream ofs("/home/box/result.out");
    
    while (std::getline(std::cin, buf))
    {
        // std::cout << buf << std::endl;
        ofs << buf << std::endl;
    }
    ofs.close();
    return 0;
}