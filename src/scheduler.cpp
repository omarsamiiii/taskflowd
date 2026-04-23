#include "taskflowd/scheduler.h"

namespace taskflowd {

Scheduler::Scheduler(Workflow& workflow)
    : workflow_(workflow) {}

std::vector<std::string> Scheduler::readyJobs() const {
    std::vector<std::string> ready;

    for (const auto& job : workflow_.jobs()) {
        if (job.status != JobStatus::Pending) {
            continue;
        }

        bool dependenciesSucceeded = true;

        for (const auto& depId : job.dependencies) {
            const auto* dep = workflow_.findJob(depId);

            if (dep == nullptr || dep->status != JobStatus::Succeeded) {
                dependenciesSucceeded = false;
                break;
            }
        }

        if (dependenciesSucceeded) {
            ready.push_back(job.id);
        }
    }

    return ready;
}

bool Scheduler::markRunning(const std::string& id) {
    auto* job = workflow_.findJob(id);
    if (job == nullptr || job->status != JobStatus::Pending) {
        return false;
    }

    job->status = JobStatus::Running;
    return true;
}

bool Scheduler::markSucceeded(const std::string& id) {
    auto* job = workflow_.findJob(id);
    if (job == nullptr || job->status != JobStatus::Running) {
        return false;
    }

    job->status = JobStatus::Succeeded;
    return true;
}

bool Scheduler::markFailed(const std::string& id) {
    auto* job = workflow_.findJob(id);
    if (job == nullptr || job->status != JobStatus::Running) {
        return false;
    }

    job->status = JobStatus::Failed;
    return true;
}

} // namespace taskflowd