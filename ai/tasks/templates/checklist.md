# Task Checklist: [TASK_ID]

## Task: [Task Title]

### Pre-execution
- [ ] Read task.json and understand acceptance criteria
- [ ] Identify all input files and dependencies
- [ ] Verify all required context is available

### Execution Steps
- [ ] Step 1: [Specific action to take]
- [ ] Step 2: [Next specific action]
- [ ] Step 3: [Continue with ordered steps]

### Validation
- [ ] Code compiles without warnings
- [ ] No unused abstractions introduced
- [ ] Public interfaces are minimal and justified
- [ ] No per-frame dynamic allocations in hot paths
- [ ] Ownership and lifetimes are explicit
- [ ] All acceptance criteria met

### Completion
- [ ] All steps marked complete
- [ ] progress.ndjson contains task_completed event
- [ ] No validation rules violated

---

**Notes:**
- Mark steps with `[x]` only after validation succeeds
- Never mark multiple steps at once
- Log each step completion to progress.ndjson
