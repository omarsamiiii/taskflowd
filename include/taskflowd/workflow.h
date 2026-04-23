#pragma once

#include "taskflowd/job.h"

#include <string>
#include <vector>

namespace taskflowd {

class Workflow {
public:
    void addJob(const Job& job);
    const std::vector<Job>& jobs() const;

    std::vector<std::string> validate() const;

private:
    std::vector<Job> jobs_;
};

} // namespace taskflowd