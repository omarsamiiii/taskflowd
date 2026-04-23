#pragma once

#include <string>
#include <vector>

namespace taskflowd {

enum class JobStatus {
    Pending,
    Running,
    Succeeded,
    Failed,
    Skipped
};

struct Job {
    std::string id;
    std::string command;
    std::vector<std::string> dependencies;
    JobStatus status = JobStatus::Pending;
};

} // namespace taskflowd