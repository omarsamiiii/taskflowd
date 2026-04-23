#pragma once

#include "taskflowd/workflow.h"

#include <string>
#include <vector>

namespace taskflowd {

struct ValidationResult {
    std::vector<std::string> errors;

    bool ok() const {
        return errors.empty();
    }
};

ValidationResult validateWorkflow(const Workflow& workflow);

} // namespace taskflowd