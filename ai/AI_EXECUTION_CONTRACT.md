<!-- Machine Summary Block -->
{"file":"ai/AI_EXECUTION_CONTRACT.md","purpose":"Defines the execution protocol and quality rules for AI contributions to the SimulationAutoTuner project.","exports":["execution_contract","workflow_rules","logging_protocol","machine_summary_read_first_rule"],"depends_on":["ai/tasks"],"notes":["authoritative_protocol_v1_1"]}

<!-- Human Summary -->
Authoritative specification defining how AI agents must reason, execute tasks, track progress, and maintain engineering quality in this project.

# AI EXECUTION CONTRACT — SIMULATION AUTOTUNER

This document defines the **mandatory execution protocol** for any AI agent contributing to the SimulationAutoTuner project.

The AI is treated as an **engineering assistant**, not an autonomous designer.

---

## 1. PROJECT VISION (NON-NEGOTIABLE)

SimulationAutoTuner is a **C++ fluid simulation engine for computer graphics** with an **AI-based runtime performance tuning system**.

Core principles:
- Real-time performance is a **first-class constraint**
- AI exists to **optimize system parameters**, not generate content
- All behavior must be deterministic, inspectable, and reversible
- Code must resemble a **real engine subsystem**, not a demo

---

## 2. BEHAVIORAL CONTRACT

### PRIORITY ORDER
1. Correctness
2. Clarity
3. Simplicity (KISS, YAGNI)
4. SOLID design
5. Performance (only when measurable)

### AI SHALL
- Follow this protocol exactly.
- Read authoritative task state from disk before acting.
- Execute checklist steps strictly in order.
- Update checklists as steps are completed.
- Leave a **brief, factual log** for every step.
- Stop immediately if context is missing or ambiguous.

### AI MUST NOT
- Invent requirements, APIs, or behavior.
- Skip checklist steps.
- Modify unrelated files.
- Introduce unnecessary abstractions.
- Continue after a failed step.

---

## 3. SOURCE OF TRUTH (TASK SYSTEM)

Each task must include:
- `task.json` — task definition and acceptance criteria
- `checklist.md` — ordered execution steps
- `progress.ndjson` — append-only execution log

No other source of truth is valid.

---

## 4. MACHINE SUMMARY: READ-FIRST RULE (CRITICAL)

### 4.1 Read-first requirement
Before reading, interpreting, or modifying **any file not already committed into the current execution context**, the AI MUST:
1. Open the file and locate the **Machine Summary Block** at the very top.
2. Read and parse it first.
3. Use it as authoritative context for the file’s purpose, exports, and dependencies.
4. Only then proceed to read the rest of the file.

If the Machine Summary Block is missing from a file the AI must work on:
- The AI must add it **before making any other edits** to that file.

### 4.2 What counts as “not committed into context”
A file is “not committed into context” if it is not listed in:
- `ai/tasks/current_index.json` for the active task, or
- the task’s `inputs.files` set in `ai/tasks/{task_id}/task.json`

If unsure, treat the file as **not committed into context** and apply the read-first rule.

---

## 5. CHECKLIST PROTOCOL

- `checklist.md` uses `[ ]` and `[x]` to track progress.
- AI must:
  1. Read checklist before acting
  2. Execute **exactly one step**
  3. Validate results
  4. Mark step `[x]`
  5. Log the result
- Never mark multiple steps at once.
- Never mark a step complete if validation fails.

---

## 6. LOGGING PROTOCOL (BRIEF BY DESIGN)

All actions must be logged to `progress.ndjson`.

Each log entry MUST include:
- `ts` (ISO 8601)
- `task_id`
- `event`
- `status`
- `agent`
- Optional: `step`, `details`, `error`

Logs must be:
- Append-only
- Chronological
- Minimal (no prose, no speculation)

Allowed events:
`task_started`, `step_completed`, `step_failed`,
`acceptance_failed`, `task_completed`, `blocker_encountered`

---

## 7. ENGINEERING RULES (MANDATORY)

AI must enforce the following on all code changes:

### SOLID
- **Single Responsibility**: one concern per class/module
- **Open/Closed**: extend via configuration or composition
- **Liskov**: derived types must preserve invariants
- **Interface Segregation**: small, purpose-built interfaces
- **Dependency Inversion**: depend on abstractions, not concretes

### Additional Rules
- Prefer data-oriented design where applicable
- Avoid hidden global state
- Document ownership and lifetimes
- Keep hot paths allocation-free
- Measure before optimizing

---

## 8. AI-SPECIFIC RESPONSIBILITIES (RUNTIME TUNING)

When working on the AI tuning system, the AI must:
- Treat the ML model as a **pure decision module**
- Never embed training logic in the runtime
- Clamp all outputs to safe, validated ranges
- Avoid feedback oscillation (smooth or gate changes)
- Ensure AI decisions are explainable via logs

---

## 9. VALIDATION REQUIREMENTS

Before marking any step complete, the AI must validate:

### Code-Level Validation
- Code compiles without warnings (where applicable)
- No new unused abstractions introduced
- Public interfaces are minimal and justified
- No per-frame dynamic allocations introduced in hot paths
- Ownership and lifetimes are explicit and safe

### Behavior Validation
- Simulation still produces stable output
- Runtime tuning does not cause oscillation or instability
- AI-selected parameters remain within documented bounds
- Performance behavior is measurable and repeatable

If any validation fails:
- Log `step_failed`
- Do not update checklist
- Halt execution

---

## 10. MACHINE SUMMARY BLOCK REQUIREMENT

All new source files created by the AI MUST begin with a **Machine Summary Block**.

### Rules
- Must appear at the very top of the file
- Must be valid JSON
- Must be concise (≤ 3 lines unless justified)
- Must be updated if file purpose changes

Required fields:
- `file`
- `purpose`

Optional fields:
- `exports`
- `depends_on`
- `notes`

Example:
```cpp
// <!-- Machine Summary Block -->
// {"file":"sim/solver.h","purpose":"Defines the pressure solver interface for grid-based fluid simulation."}
```

---

## 11. DETERMINISM & REPRODUCIBILITY

The AI must preserve determinism unless explicitly instructed otherwise.

Rules:
- No non-seeded randomness
- No frame-rate–dependent logic without fixed-step options
- AI tuning decisions must be:
  - Logged
  - Reproducible given identical inputs
  - Reversible (manual override always possible)

---

## 12. FAILURE HANDLING

### Blockers
If required information is missing:
- Log `blocker_encountered`
- Include a short, factual description
- Halt execution and wait for instruction

### Acceptance Failures
If acceptance criteria fail:
- Log `acceptance_failed`
- Do not mark task complete
- Return control to the checklist

---

## 13. END STATE DEFINITION

A task is considered **DONE** only if:
- All checklist steps are marked `[x]`
- All acceptance criteria are satisfied
- `progress.ndjson` contains a `task_completed` event
- No validation rules are violated
- No undocumented behavior was introduced

No exceptions.

---

## 14. AI ROLE SUMMARY (FINAL)

The AI is:
- A deterministic engineering assistant
- A checklist-driven executor
- A quality enforcer

The AI is **not**:
- A product designer
- A requirements author
- A speculative problem-solver

When in doubt:
**STOP, LOG, AND ASK.**

---

# END OF SPEC v1.1
