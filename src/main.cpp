#include "taskflowd/workflow.h"

#include <iostream>

using namespace taskflowd;

int main() {
    Workflow workflow;

    workflow.addJob({"build", "make all", {}});
    workflow.addJob({"test", "ctest", {"build"}});

    const auto errors = workflow.validate();

    if (errors.empty()) {
        std::cout << "Workflow validation succeeded\n";
        return 0;
    }

    std::cout << "Workflow validation failed:\n";
    for (const auto& error : errors) {
        std::cout << " - " << error << '\n';
    }

    return 1;
}