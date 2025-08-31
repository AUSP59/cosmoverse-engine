
# Architecture Diagram
```mermaid
flowchart TD
  CLI[cosmoverse CLI] -->|uses| Lib[libcosmoverse]
  Lib --> Logger
  Lib --> ThreadPool
  Logger --> Stdout
```
