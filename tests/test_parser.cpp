#include "taskflowd/parser.h"

#include <cassert>

using namespace taskflowd;

static void parses_single_job() {
    const auto result = parseWorkflowText(R"(
job build
  command: make all
)");

    assert(result.ok());
    assert(result.workflow.jobs().size() == 1);
    assert(result.workflow.jobs()[0].id == "build");
    assert(result.workflow.jobs()[0].command == "make all");
}

static void parses_dependencies() {
    const auto result = parseWorkflowText(R"(
job build
  command: make all

job test
  command: ctest
  depends: build
)");

    assert(result.ok());
    assert(result.workflow.jobs().size() == 2);
    assert(result.workflow.jobs()[1].dependencies.size() == 1);
    assert(result.workflow.jobs()[1].dependencies[0] == "build");
}

static void parses_comma_separated_dependencies() {
    const auto result = parseWorkflowText(R"(
job package
  command: tar -czf out.tgz build/
  depends: build, test
)");

    assert(result.ok());
    assert(result.workflow.jobs().size() == 1);
    assert(result.workflow.jobs()[0].dependencies.size() == 2);
}

static void rejects_property_before_job() {
    const auto result = parseWorkflowText(R"(
command: make all
)");

    assert(!result.ok());
}

static void rejects_unknown_property() {
    const auto result = parseWorkflowText(R"(
job build
  command: make all
  timeout: 30
)");

    assert(!result.ok());
}

int main() {
    parses_single_job();
    parses_dependencies();
    parses_comma_separated_dependencies();
    rejects_property_before_job();
    rejects_unknown_property();
    return 0;
}