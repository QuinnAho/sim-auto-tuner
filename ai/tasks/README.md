<!-- Machine Summary Block -->
{"file":"ai/tasks/README.md","purpose":"Explains the task tracking system required by the AI Execution Contract.","depends_on":["ai/AI_EXECUTION_CONTRACT.md"],"notes":["task_system_documentation"]}

<!-- Human Summary -->
Documentation for the AI task tracking system: task.json, checklist.md, and progress.ndjson files.

# AI Task System

This directory contains the task tracking system required by the **AI Execution Contract**.

## Directory Structure

```
ai/tasks/
├── current_index.json          # Tracks the currently active task
├── templates/                  # Template files for new tasks
│   ├── task.json
│   ├── checklist.md
│   └── progress.ndjson
└── {task_id}/                  # One directory per task
    ├── task.json               # Task definition and acceptance criteria
    ├── checklist.md            # Ordered execution steps
    └── progress.ndjson         # Append-only execution log
```

## Core Files (Required per Task)

### 1. task.json
**Purpose:** Defines the task, acceptance criteria, and expected inputs/outputs.

**Required fields:**
- `task_id` - Unique identifier
- `title` - Brief task title
- `description` - Detailed description
- `created` - ISO 8601 timestamp
- `status` - Current status (pending/in_progress/completed/failed/blocked)
- `acceptance_criteria` - Array of measurable conditions

**Optional fields:**
- `inputs.files` - Files needed for the task
- `inputs.context` - Additional context
- `outputs.expected_files` - Files expected to be created/modified
- `priority` - Task priority

### 2. checklist.md
**Purpose:** Ordered execution steps tracked with `[ ]` and `[x]`.

**Rules:**
- Execute steps strictly in order
- Mark `[x]` only after validation succeeds
- Never mark multiple steps at once
- If a step fails, halt and log

**Standard sections:**
- Pre-execution (read task, verify context)
- Execution Steps (ordered actions)
- Validation (code quality checks)
- Completion (final verification)

### 3. progress.ndjson
**Purpose:** Append-only chronological log of all task actions.

**Required fields per entry:**
- `ts` - ISO 8601 timestamp
- `task_id` - Task identifier
- `event` - Event type (see below)
- `status` - Current status
- `agent` - AI agent identifier

**Allowed events:**
- `task_started`
- `step_completed`
- `step_failed`
- `acceptance_failed`
- `task_completed`
- `blocker_encountered`

**Optional fields:**
- `step` - Which step was executed
- `details` - Brief factual description
- `error` - Error description (for failures)

## Workflow

### Creating a New Task

1. Create task directory: `ai/tasks/{task_id}/`
2. Copy templates to the task directory
3. Fill out `task.json` with specific requirements
4. Customize `checklist.md` with ordered steps
5. Initialize `progress.ndjson` with `task_started` event
6. Update `current_index.json` to reference the new task

### Executing a Task

1. **Read** `task.json` to understand acceptance criteria
2. **Read** `checklist.md` to see execution order
3. **Execute** one step at a time
4. **Validate** the result
5. **Mark** step complete `[x]` in checklist
6. **Log** the action to `progress.ndjson`
7. **Repeat** until all steps complete

### Task Completion Criteria

A task is **DONE** only when:
- All checklist steps marked `[x]`
- All acceptance criteria satisfied
- `progress.ndjson` contains `task_completed` event
- No validation rules violated
- No undocumented behavior introduced

## Example: Creating a Simple Task

```bash
# 1. Create task directory
mkdir -p ai/tasks/TASK_001_add_logging

# 2. Copy templates
cp ai/tasks/templates/* ai/tasks/TASK_001_add_logging/

# 3. Edit task.json with specific requirements
# 4. Edit checklist.md with ordered steps
# 5. Initialize progress.ndjson with task_started event
# 6. Update current_index.json
```

## Integration with AI Execution Contract

This task system enforces:
- **Section 3:** Source of truth (task.json, checklist.md, progress.ndjson)
- **Section 5:** Checklist protocol (strict step ordering)
- **Section 6:** Logging protocol (NDJSON format)
- **Section 9:** Validation requirements (before marking complete)
- **Section 12:** Failure handling (blocker logging)
- **Section 13:** End state definition (completion criteria)

## Tips for AI Agents

1. **Always read before acting** - Load task state from disk
2. **One step at a time** - Never batch operations
3. **Validate before marking** - Ensure step succeeded
4. **Log everything** - Keep progress.ndjson up to date
5. **Stop on ambiguity** - Use `blocker_encountered` when stuck
6. **No speculation** - Only execute defined steps

---

For the full specification, see: `ai/AI_EXECUTION_CONTRACT.md`
