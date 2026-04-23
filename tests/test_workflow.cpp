#include "taskflowd/workflow.h"

#include <cassert>
#include <string>
#include <vector>

using namespace taskflowd;

static void test_valid_workflow_has_no_errors() {
    Workflow workflow;
    workflow.addJob({"build", "make all", {}});
    workflow.addJob({"test", "ctest", {"build"}});

    const auto errors = workflow.validate();
    assert(errors.empty());
}

static void test_duplicate_job_ids_are_reported() {
    Workflow workflow;
    workflow.addJob({"build", "make all", {}});
    workflow.addJob({"build", "make test", {}});

    const auto errors = workflow.validate();
    assert(!errors.empty());
}

static void test_missing_dependency_is_reported() {
    Workflow workflow;
    workflow.addJob({"test", "ctest", {"build"}});

    const auto errors = workflow.validate();
    assert(!errors.empty());
}

int main() {
    test_valid_workflow_has_no_errors();
    test_duplicate_job_ids_are_reported();
    test_missing_dependency_is_reported();
    return 0;
}