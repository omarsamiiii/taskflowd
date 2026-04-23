# taskflowd

taskflowd is a lightweight C++ workflow runner for dependency-based local job execution.

## Current scope

This repository currently includes:

- a basic `Job` model
- a `Workflow` container
- workflow validation for:
  - duplicate job IDs
  - unknown dependencies
- a minimal CLI example
- basic tests

## Build

```bash
./scripts/build.sh