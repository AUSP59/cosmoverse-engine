
# ADR-0001: Thread Pool Design
- Fixed-size pool with work-stealing is out of scope for now; we use a simple queue + worker threads.
- Rationale: minimize dependencies, clarity, predictable behavior.
- Consequences: simpler code; consider work-stealing in future if workloads demand it.
