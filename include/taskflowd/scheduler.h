#pragma once

#include "taskflowd/workflow.h"

#include <string>
#include <vector>

namespace taskflowd {

class Scheduler {
public:
    explicit Scheduler(Workflow& workflow);

    std::vector<std::string> readyJobs() const;

    bool markRunning(const std::string& id);
    bool markSucceeded(const std::string& id);
    bool markFailed(const std::string& id);

private:
    Workflow& workflow_;
};

} // namespace taskflowd