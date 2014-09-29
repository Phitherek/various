#include "BranchDetector.h"
#include <iostream>
#include <cstdlib>
using namespace std;
using namespace GitPermissionRepairer;

int main(int argc, char** argv) {
    if(argc != 2) {
        cout << "Usage: " << argv[0] << " <repository_path>" << endl;
    } else {
        BranchDetector bd(argv[1]);
        std::string bname;
        while(!bd.end()) {
            bname = bd.getNextBranch();
            if(bname != "") {
                cout << bname << endl;
            }
        }
    }
    return EXIT_SUCCESS;
}
