# VerPart Module

This folder implements the **Vertical Partitioning (VerPart)** stage of the disassociation algorithm.

In this step, we take the horizontally partitioned clusters produced by `HorPart` and split each one **vertically** into item chunks (groups of diagnosis codes), while preserving k^m-anonymity and respecting utility constraints.

This implementation follows the process described in:
📄 [Disassociation for Electronic Health Record Privacy](https://www.sciencedirect.com/science/article/pii/S1532046414001269#s0065) (Section: Vertical Partitioning)

## How It Works

1. **Input**:

   - A list of clusters from HorPart (each a group of patient records)
   - Utility constraints (same JSON file as in HorPart)
   - Parameters `k` and `m`

2. **Vertical Partitioning**:

   - For each cluster:
     - Codes that appear in fewer than `k` records are grouped into a **TT item chunk**
     - Remaining codes are grouped based on utility constraints and projected onto new **record chunks**
     - Each record chunk must have support ≥ `k`

3. **Output**:
   - For each cluster, we produce:
     - `record_chunks`: groups of projected records per code group
     - `item_chunk`: the TT chunk (low-support codes)
     - `shared_chunks`: initialized as empty (populated after refinement)
   - The full disassociated output is saved as a JSON file

## Data Flow

### Step 1 — HorPart Input

The vertical partitioning receives clusters like the following (output from HorPart):

```
Cluster 1:
944.01 296.02 296.01 834.0 296.00
695.10 296.01 692.71 944.01 296.02 401.0 296.00
692.71 296.02 695.10 834.0 296.00
692.71 296.01 401.0 296.00
692.71 296.02 296.01 695.10 296.00
-------------------
Cluster 2:
296.03 295.04 404.00 480.1
294.10 296.03 834.0 944.01
294.10 295.04 296.03 480.1
294.10 295.04 404.00
294.10 295.04 296.03 834.0 944.01
-------------------
```

Utility constraints remain the same as in HorPart:

📄 `data/utility_constraints.json`

```json
{
  "u1": ["294.10", "295.04", "296.00", "296.01", "296.02", "296.03"],
  "u2": ["692.71", "695.10"],
  "u3": ["401.0", "404.00"],
  "u4": ["480.1"],
  "u5": ["834.0", "944.01"]
}
```

### Step 2 — Partitioning & Grouping

- Compute support for each code
- Group codes with support < k into TT (item_chunk)
- Assign remaining codes to groups based on utility constraints
- Project records onto code groups to form record_chunks (must meet k support)

### Step 3 — Output (JSON)

The final result is written to a file like toy_example_output.json:

```
{
  "clusters": [
    {
      "record_chunks": [[ ... ], [ ... ]],
      "item_chunk": [[ "692.71", "695.10" ]],
      "shared_chunks": []
    },
    ...
  ]
}
```

## Illustrations (from paper)

You can refer to the pseudocode and transformation diagrams from the original paper:

- [Original dataset](https://www.sciencedirect.com/science/article/pii/S1532046414001269#f0005)
- [Utility constraints (b)](https://www.sciencedirect.com/science/article/pii/S1532046414001269#f0015)
- [Disassociation algorithm](https://www.sciencedirect.com/science/article/pii/S1532046414001269#f0030)
- [Notation](https://www.sciencedirect.com/science/article/pii/S1532046414001269#f0035)
- [VerPart algorithm](https://www.sciencedirect.com/science/article/pii/S1532046414001269#f0045)
- [Output of vertical partitioning](https://www.sciencedirect.com/science/article/pii/S1532046414001269#f0020)
