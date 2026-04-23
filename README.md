# taskflowd

taskflowd is a lightweight C++ workflow runner for dependency-based local job execution.

The project is intentionally early-stage, but it is structured like a real maintainable C++ tool.

## Current capabilities

- Defines jobs with commands and dependencies
- Parses a simple workflow file format
- Validates workflows
- Reports:
  - duplicate job IDs
  - empty job IDs
  - missing commands
  - unknown dependencies
  - direct and indirect dependency cycles
- Computes which jobs are ready to run based on dependency status
- Provides a small CLI

## Workflow format

Example:

```text
job build
  command: make all

job test
  command: ctest
  depends: build