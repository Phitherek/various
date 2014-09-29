#include "BranchDetector.h"
#include "Exceptions.h"
#include <iostream>
#include <cstdio>
#include <unistd.h>
using namespace GitPermissionRepairer;

BranchDetector::BranchDetector(std::string repopath) {
    chdir(repopath.c_str());
    FILE* bout = popen("git rev-parse --abbrev-ref --branches", "r");
    char* buffer = new char[100];
    if(bout == NULL) {
        std::string err = "";
		err += "Could not open command output: git branch!";
		throw FileException(err);
    }
    while(!feof(bout)) {
        for(int i = 0; i < 100; i++) {
            buffer[i] = '\0';
        }
        fscanf(bout, "%s", buffer);
        std::string bstr(buffer);
        if(bstr != "" && bstr != "local") {
            _branches.push_back(bstr);
        }
    }
    delete[] buffer;
    fclose(bout);
    _lastindex = -1;
}

std::string BranchDetector::getNextBranch() {
    int bsize = _branches.size();
    if(_lastindex < bsize-1) {
        _lastindex++;
        return _branches[_lastindex];
    } else if(_lastindex < bsize) {
        _lastindex++;
        return "";
    } else {
        return "";
    }
}

bool BranchDetector::end() {
    int bsize = _branches.size();
    if(_lastindex < bsize) {
        return false;
    }
    return true;
}

void BranchDetector::reset() {
    _lastindex = -1;
}
