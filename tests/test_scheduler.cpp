#include "taskflowd/scheduler.h"

#include <algorithm>
#include <cassert>
#include <vector>

using namespace taskflowd;

static bool contains(const std::vector<std::string>& values, const std::string& target) {
    return std::find(values.begin(), values.end(), target) != values.end();
}

static void jobs_without_dependencies_are_ready() {
    Workflow workflow;
    workflow.addJob({"build", "make all", {}});

    Scheduler scheduler(workflow);
    const auto ready = scheduler.readyJobs();

    assert(ready.size() == 1);
    assert(contains(ready, "build"));
}

static void job_waits_for_dependencies() {
    Workflow workflow;
    workflow.addJob({"build", "make all", {}});
    workflow.addJob({"test", "ctest", {"build"}});

    Scheduler scheduler(workflow);
    const auto ready = scheduler.readyJobs();

    assert(ready.size() == 1);
    assert(contains(ready, "build"));
    assert(!contains(ready, "test"));
}

static void dependency_success_makes_downstream_job_ready() {
    Workflow workflow;
    workflow.addJob({"build", "make all", {}});
    workflow.addJob({"test", "ctest", {"build"}});

    Scheduler scheduler(workflow);

    assert(scheduler.markRunning("build"));
    assert(scheduler.markSucceeded("build"));

    const auto ready = scheduler.readyJobs();

    assert(ready.size() == 1);
    assert(contains(ready, "test"));
}

static void failed_dependency_does_not_make_downstream_ready() {
    Workflow workflow;
    workflow.addJob({"build", "make all", {}});
    workflow.addJob({"test", "ctest", {"build"}});

    Scheduler scheduler(workflow);

    assert(scheduler.markRunning("build"));
    assert(scheduler.markFailed("build"));

    const auto ready = scheduler.readyJobs();

    assert(ready.empty());
}

static void cannot_mark_pending_job_succeeded_directly() {
    Workflow workflow;
    workflow.addJob({"build", "make all", {}});

    Scheduler scheduler(workflow);

    assert(!scheduler.markSucceeded("build"));
}

int main() {
    jobs_without_dependencies_are_ready();
    job_waits_for_dependencies();
    dependency_success_makes_downstream_job_ready();
    failed_dependency_does_not_make_downstream_ready();
    cannot_mark_pending_job_succeeded_directly();
    return 0;
}