#pragma once

#include "taskflowd/job.h"

#include <optional>
#include <string>
#include <vector>

namespace taskflowd {

class Workflow {
public:
    bool addJob(const Job& job);

    const std::vector<Job>& jobs() const;
    std::vector<Job>& jobs();

    const Job* findJob(const std::string& id) const;
    Job* findJob(const std::string& id);

private:
    std::vector<Job> jobs_;
};

} // namespace taskflowd