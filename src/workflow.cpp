#include "taskflowd/workflow.h"

namespace taskflowd {

bool Workflow::addJob(const Job& job) {
    jobs_.push_back(job);
    return true;
}

const std::vector<Job>& Workflow::jobs() const {
    return jobs_;
}

std::vector<Job>& Workflow::jobs() {
    return jobs_;
}

const Job* Workflow::findJob(const std::string& id) const {
    for (const auto& job : jobs_) {
        if (job.id == id) {
            return &job;
        }
    }
    return nullptr;
}

Job* Workflow::findJob(const std::string& id) {
    for (auto& job : jobs_) {
        if (job.id == id) {
            return &job;
        }
    }
    return nullptr;
}

} // namespace taskflowd