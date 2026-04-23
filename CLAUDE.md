## Project overview

taskflowd is a lightweight C++ workflow runner for local dependency-based job execution.

The long-term direction is:
- validate workflow graphs
- schedule runnable jobs based on dependency completion
- execute jobs safely
- expose workflow/job status clearly

This repository is intentionally still early-stage. Prefer incremental improvements over speculative architecture.

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