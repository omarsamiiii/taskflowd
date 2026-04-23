#include "taskflowd/validation.h"

#include <functional>
#include <unordered_map>
#include <unordered_set>

namespace taskflowd {

namespace {

enum class VisitState {
    Visiting,
    Visited
};

bool hasCycleFrom(
    const std::string& jobId,
    const std::unordered_map<std::string, const Job*>& jobsById,
    std::unordered_map<std::string, VisitState>& visitState,
    std::vector<std::string>& stack,
    std::vector<std::string>& errors
) {
    visitState[jobId] = VisitState::Visiting;
    stack.push_back(jobId);

    const auto jobIt = jobsById.find(jobId);
    if (jobIt == jobsById.end()) {
        stack.pop_back();
        return false;
    }

    for (const auto& dep : jobIt->second->dependencies) {
        const auto depIt = jobsById.find(dep);
        if (depIt == jobsById.end()) {
            continue;
        }

        const auto stateIt = visitState.find(dep);
        if (stateIt != visitState.end() && stateIt->second == VisitState::Visiting) {
            std::string cycle = dep;
            for (auto it = stack.rbegin(); it != stack.rend(); ++it) {
                cycle += " <- " + *it;
                if (*it == dep) {
                    break;
                }
            }

            errors.push_back("Dependency cycle detected: " + cycle);
            stack.pop_back();
            return true;
        }

        if (stateIt == visitState.end()) {
            if (hasCycleFrom(dep, jobsById, visitState, stack, errors)) {
                stack.pop_back();
                return true;
            }
        }
    }

    visitState[jobId] = VisitState::Visited;
    stack.pop_back();
    return false;
}

} // namespace

ValidationResult validateWorkflow(const Workflow& workflow) {
    ValidationResult result;
    std::unordered_map<std::string, const Job*> jobsById;
    std::unordered_set<std::string> seenIds;

    for (const auto& job : workflow.jobs()) {
        if (job.id.empty()) {
            result.errors.push_back("Job id must not be empty");
            continue;
        }

        if (!seenIds.insert(job.id).second) {
            result.errors.push_back("Duplicate job id: " + job.id);
            continue;
        }

        jobsById[job.id] = &job;
    }

    for (const auto& job : workflow.jobs()) {
        if (job.id.empty()) {
            continue;
        }

        if (job.command.empty()) {
            result.errors.push_back("Job '" + job.id + "' must have a command");
        }

        for (const auto& dep : job.dependencies) {
            if (jobsById.find(dep) == jobsById.end()) {
                result.errors.push_back(
                    "Job '" + job.id + "' references unknown dependency '" + dep + "'"
                );
            }
        }
    }

    std::unordered_map<std::string, VisitState> visitState;
    std::vector<std::string> stack;

    for (const auto& entry : jobsById) {
        if (visitState.find(entry.first) == visitState.end()) {
            hasCycleFrom(entry.first, jobsById, visitState, stack, result.errors);
        }
    }

    return result;
}

} // namespace taskflowd