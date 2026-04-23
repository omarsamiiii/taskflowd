#include "taskflowd/workflow.h"

#include <set>
#include <unordered_set>

namespace taskflowd {

void Workflow::addJob(const Job& job) {
    jobs_.push_back(job);
}

const std::vector<Job>& Workflow::jobs() const {
    return jobs_;
}

std::vector<std::string> Workflow::validate() const {
    std::vector<std::string> errors;
    std::unordered_set<std::string> ids;

    for (const auto& job : jobs_) {
        if (job.id.empty()) {
            errors.push_back("Job id must not be empty");
            continue;
        }

        if (!ids.insert(job.id).second) {
            errors.push_back("Duplicate job id: " + job.id);
        }
    }

    for (const auto& job : jobs_) {
        for (const auto& dep : job.dependencies) {
            if (ids.find(dep) == ids.end()) {
                errors.push_back("Job '" + job.id + "' references unknown dependency '" + dep + "'");
            }
        }
    }

    return errors;
}

} // namespace taskflowd