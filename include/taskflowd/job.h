#pragma once

#include <string>
#include <vector>

namespace taskflowd {

struct Job {
    std::string id;
    std::string command;
    std::vector<std::string> dependencies;
};

} // namespace taskflowd