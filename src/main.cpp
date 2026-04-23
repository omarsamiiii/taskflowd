#include "taskflowd/parser.h"
#include "taskflowd/scheduler.h"
#include "taskflowd/validation.h"

#include <iostream>

using namespace taskflowd;

namespace {

void printUsage() {
    std::cout << "Usage:\n";
    std::cout << "  taskflowd validate <workflow-file>\n";
    std::cout << "  taskflowd ready <workflow-file>\n";
}

} // namespace

int main(int argc, char** argv) {
    if (argc != 3) {
        printUsage();
        return 1;
    }

    const std::string command = argv[1];
    const std::string workflowPath = argv[2];

    auto parseResult = parseWorkflowFile(workflowPath);
    if (!parseResult.ok()) {
        std::cout << "Parse failed:\n";
        for (const auto& error : parseResult.errors) {
            std::cout << " - " << error << '\n';
        }
        return 1;
    }

    auto validationResult = validateWorkflow(parseResult.workflow);
    if (!validationResult.ok()) {
        std::cout << "Validation failed:\n";
        for (const auto& error : validationResult.errors) {
            std::cout << " - " << error << '\n';
        }
        return 1;
    }

    if (command == "validate") {
        std::cout << "Workflow validation succeeded\n";
        return 0;
    }

    if (command == "ready") {
        Scheduler scheduler(parseResult.workflow);
        const auto ready = scheduler.readyJobs();

        std::cout << "Ready jobs:\n";
        for (const auto& jobId : ready) {
            std::cout << " - " << jobId << '\n';
        }

        return 0;
    }

    printUsage();
    return 1;
}