## Project overview

taskflowd is a lightweight C++ workflow runner for local dependency-based job execution.

The long-term direction is:
- parse workflow definitions
- validate workflow graphs
- schedule runnable jobs based on dependency completion
- execute jobs safely
- expose workflow/job status clearly

This repository is intentionally early-stage. Prefer incremental improvements over speculative architecture.

## Current architecture

Important components:

- `Job`
  - Defined in `include/taskflowd/job.h`
  - Holds job id, command, dependencies, and current status

- `Workflow`
  - Defined in `include/taskflowd/workflow.h`
  - Owns the list of jobs
  - Provides lookup by job id

- `validateWorkflow`
  - Defined in `include/taskflowd/validation.h`
  - Performs semantic validation:
    - duplicate job IDs
    - missing commands
    - unknown dependencies
    - dependency cycles

- `Scheduler`
  - Defined in `include/taskflowd/scheduler.h`
  - Computes ready jobs based on dependency state
  - Updates job state transitions

- `Parser`
  - Defined in `include/taskflowd/parser.h`
  - Parses the simple text workflow format

## Development workflow

Before making changes:

1. Read the relevant headers and source files first.
2. Understand existing naming and structure.
3. Keep changes narrowly scoped to the task.

After making changes:

1. Build the project.
2. Run tests.
3. Report exactly what was verified and what was not.

## Build and test

Build:

```bash
./scripts/build.sh

test: 
```bash
./scripts/test.sh