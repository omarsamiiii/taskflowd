#include "taskflowd/parser.h"

#include <fstream>
#include <sstream>

namespace taskflowd {

namespace {

std::string trim(const std::string& input) {
    const auto start = input.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) {
        return "";
    }

    const auto end = input.find_last_not_of(" \t\r\n");
    return input.substr(start, end - start + 1);
}

bool startsWith(const std::string& value, const std::string& prefix) {
    return value.rfind(prefix, 0) == 0;
}

std::vector<std::string> splitCommaSeparated(const std::string& value) {
    std::vector<std::string> result;
    std::stringstream stream(value);
    std::string item;

    while (std::getline(stream, item, ',')) {
        auto trimmed = trim(item);
        if (!trimmed.empty()) {
            result.push_back(trimmed);
        }
    }

    return result;
}

} // namespace

ParseResult parseWorkflowText(const std::string& text) {
    ParseResult result;

    std::istringstream input(text);
    std::string line;
    Job currentJob;
    bool inJob = false;
    int lineNumber = 0;

    auto flushCurrentJob = [&]() {
        if (inJob) {
            result.workflow.addJob(currentJob);
            currentJob = Job{};
            inJob = false;
        }
    };

    while (std::getline(input, line)) {
        ++lineNumber;
        const auto trimmed = trim(line);

        if (trimmed.empty() || startsWith(trimmed, "#")) {
            continue;
        }

        if (startsWith(trimmed, "job ")) {
            flushCurrentJob();

            const auto id = trim(trimmed.substr(4));
            if (id.empty()) {
                result.errors.push_back("Line " + std::to_string(lineNumber) + ": job id is empty");
                continue;
            }

            currentJob = Job{};
            currentJob.id = id;
            inJob = true;
            continue;
        }

        if (!inJob) {
            result.errors.push_back(
                "Line " + std::to_string(lineNumber) + ": property found before any job"
            );
            continue;
        }

        if (startsWith(trimmed, "command:")) {
            currentJob.command = trim(trimmed.substr(8));
            continue;
        }

        if (startsWith(trimmed, "depends:")) {
            currentJob.dependencies = splitCommaSeparated(trim(trimmed.substr(8)));
            continue;
        }

        result.errors.push_back(
            "Line " + std::to_string(lineNumber) + ": unknown property '" + trimmed + "'"
        );
    }

    flushCurrentJob();

    return result;
}

ParseResult parseWorkflowFile(const std::string& path) {
    std::ifstream file(path);
    ParseResult result;

    if (!file) {
        result.errors.push_back("Unable to open workflow file: " + path);
        return result;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return parseWorkflowText(buffer.str());
}

} // namespace taskflowd