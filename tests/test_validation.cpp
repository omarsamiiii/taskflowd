#include "taskflowd/validation.h"

#include <cassert>

using namespace taskflowd;

static void valid_workflow_has_no_errors() {
    Workflow workflow;
    workflow.addJob({"build", "make all", {}});
    workflow.addJob({"test", "ctest", {"build"}});

    const auto result = validateWorkflow(workflow);
    assert(result.ok());
}

static void duplicate_job_ids_are_reported() {
    Workflow workflow;
    workflow.addJob({"build", "make all", {}});
    workflow.addJob({"build", "make test", {}});

    const auto result = validateWorkflow(workflow);
    assert(!result.ok());
}

static void unknown_dependency_is_reported() {
    Workflow workflow;
    workflow.addJob({"test", "ctest", {"build"}});

    const auto result = validateWorkflow(workflow);
    assert(!result.ok());
}

static void direct_cycle_is_reported() {
    Workflow workflow;
    workflow.addJob({"build", "make all", {"build"}});

    const auto result = validateWorkflow(workflow);
    assert(!result.ok());
}

static void indirect_cycle_is_reported() {
    Workflow workflow;
    workflow.addJob({"a", "echo a", {"c"}});
    workflow.addJob({"b", "echo b", {"a"}});
    workflow.addJob({"c", "echo c", {"b"}});

    const auto result = validateWorkflow(workflow);
    assert(!result.ok());
}

static void empty_command_is_reported() {
    Workflow workflow;
    workflow.addJob({"build", "", {}});

    const auto result = validateWorkflow(workflow);
    assert(!result.ok());
}

int main() {
    valid_workflow_has_no_errors();
    duplicate_job_ids_are_reported();
    unknown_dependency_is_reported();
    direct_cycle_is_reported();
    indirect_cycle_is_reported();
    empty_command_is_reported();
    return 0;
}