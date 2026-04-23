#pragma once

#include "taskflowd/workflow.h"

#include <string>
#include <vector>

namespace taskflowd {

struct ParseResult {
    Workflow workflow;
    std::vector<std::string> errors;

    bool ok() const {
        return errors.empty();
    }
};

ParseResult parseWorkflowFile(const std::string& path);
ParseResult parseWorkflowText(const std::string& text);

} // namespace taskflowd