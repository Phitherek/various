#ifndef _BRANCHDETECTOR_H
#define _BRANCHDETECTOR_H
#include <string>
#include <vector>
/// \file BranchDetector.h
/// \brief A class that detects and stores repository' s branches
/// \author Phitherek_
/// \date 2014
/// \version 0.2

/// \namespace GitPermissionRepairer
/// \brief A global namespace for Git Permission Repairer
namespace GitPermissionRepairer {
    /// \class BranchDetector
    /// \brief A class that detects and stores repository' s branches
    class BranchDetector {
        private:
            std::vector<std::string> _branches;
            int _lastindex;
        public:
            BranchDetector(std::string repopath); ///< \brief A constructor that parses and stores repository' s branches
            ///< \param repopath Path to repository
            std::string getNextBranch(); ///< \brief Gets next branch' s name
            ///< \return A name of the next branch
            bool end(); ///< \brief Returns if all branches have been iterated through
            ///< \return True if all the branches have been iterated through, false otherwise
            void reset(); ///< Resets the branch iterator
    };
}
#endif
