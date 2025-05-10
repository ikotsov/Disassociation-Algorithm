# HorPart Module

This folder implements the **Horizontal Partitioning (HorPart)** stage of the disassociation algorithm.

In this implementation, we aim to reproduce the exact example and dataset shown in the paper:
📄 [Disassociation for Electronic Health Record Privacy](https://www.sciencedirect.com/science/article/pii/S1532046414001269#s0065) (Section: Horizontal partitioning)

## How It Works

1. **Input**: a dataset (CSV format) and utility constraints (JSON)
2. **Recursive Partitioning**:
   - Recursively splits the dataset based on the most frequent diagnosis code
   - Follows utility preservation rules (preferring codes in utility constraints)
3. **Output**: a list of clusters (subsets of patient records)

## Data Flow

### Step 1 — Raw Input (CSV + JSON)

📄 `data/dataset.csv`

```
296.00,296.01,296.02,834.0,944.01
296.00,296.02,296.01,401.0,944.01,692.71,695.10
296.00,296.02,692.71,834.0,695.10
296.00,296.01,692.71,401.0
296.00,296.01,296.02,692.71,695.10
296.03,295.04,404.00,480.1
294.10,296.03,834.0,944.01
294.10,295.04,296.03,480.1
294.10,295.04,404.00
294.10,295.04,296.03,834.0,944.01
```

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

### Step 2 — Transformation

The algorithm computes the frequency of each code, filters out previously used ones, and selects the best splitting code `a`. Then it recursively partitions the dataset based on whether records contain `a`.

### Step 3 — Final Clusters

Printed to console as:

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

## Illustrations (from paper)

You can refer to the pseudocode and transformation diagrams from the original paper:

- [Original dataset](https://www.sciencedirect.com/science/article/pii/S1532046414001269#f0005)
- [Utility constraints (b)](https://www.sciencedirect.com/science/article/pii/S1532046414001269#f0015)
- [Disassociation algorithm](https://www.sciencedirect.com/science/article/pii/S1532046414001269#f0030)
- [Notation](https://www.sciencedirect.com/science/article/pii/S1532046414001269#f0035)
- [HorPart algorithm](https://www.sciencedirect.com/science/article/pii/S1532046414001269#f0040)
- [Output of horizontal partitioning](https://www.sciencedirect.com/science/article/pii/S1532046414001269#f0055)

These show how diagnosis codes are selected and how the utility constraints affect partitioning.
