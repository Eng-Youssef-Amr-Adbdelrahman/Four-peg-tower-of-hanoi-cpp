# 🗼 Four-Peg Tower of Hanoi — Divide & Conquer + Dynamic Programming

> **Course:** CSE245 – Advanced Algorithms and Complexity  
> **Task:** 3 of 10 &nbsp;|&nbsp; **Team:** 20 &nbsp;|&nbsp; **Author:** Youssef Amr Abdelrahman (ID: 23P0257)  
> **Language:** C++17 &nbsp;|&nbsp; **University:** Ain Shams University

---

## 📌 Problem Statement

There are **8 disks** of different sizes and **4 pegs**.  
Initially, all disks are stacked on the first peg — largest at the bottom, smallest on top.

**The task has three parts:**
1. Use **Divide and Conquer** to transfer all disks to another peg, one at a time, without placing a larger disk on a smaller one.
2. Determine whether a **Dynamic Programming** algorithm can solve the puzzle in exactly **33 moves**.
3. Design a **general DP algorithm** that works for **any number of disks** on 4 pegs.

---

## 📂 Repository Structure

```
Four-peg-tower-of-hanoi-cpp/
│
├── README.md
│
├── code/
│   ├── task3_hanoi.cpp                        ← Full C++17 implementation
│   └── Task3_Code_Screenshots_And_Output.pdf  ← Code + output screenshots
│
└── report/
    └── Task3_Research_Report.pdf              ← 28-page research report
```

---

## 🧠 Algorithms Implemented

### 1. Divide & Conquer — Frame-Stewart Algorithm

The four-peg problem is split into three recursive steps:

```
hanoi4(n disks, A → D using B, C):
  Step 1 → Move top k disks:    A → B  (using all 4 pegs)
  Step 2 → Move bottom (n-k):   A → D  (using only 3 pegs)
  Step 3 → Move k disks back:   B → D  (using all 4 pegs)
```

The optimal `k` that minimises total moves is determined by the DP layer.

### 2. Dynamic Programming — Bottom-Up Optimisation

The recurrence solved:

```
T(n, 4) = min over k in [1, n-1] of:  2·T(k, 4) + T(n-k, 3)

where:  T(n, 3) = 2ⁿ − 1   (classic 3-peg result)
        T(0, 4) = 0
        T(1, 4) = 1
```

Built bottom-up in **O(n²) time** and **O(n) space**.

---

## ✅ Key Results

| n (disks) | T(n,4) optimal moves | kopt | T(n,3) baseline |
|:---------:|:--------------------:|:----:|:---------------:|
| 1 | 1  | 1 | 1   |
| 2 | 3  | 1 | 3   |
| 3 | 5  | 2 | 7   |
| 4 | 9  | 2 | 15  |
| 5 | 13 | 3 | 31  |
| 6 | 17 | 3 | 63  |
| 7 | 25 | 4 | 127 |
| **8** | **33** | **4** | **255** |

> 🎯 **Yes — DP solves the 8-disk, 4-peg puzzle in exactly 33 moves.**  
> This is a **7.7× improvement** over the classical 3-peg solution (255 moves).

---

## 🚀 How to Run

**Prerequisites:** A C++17-compatible compiler (`g++`, `clang++`, or MSVC)

```bash
# Clone the repo
git clone https://github.com/Eng-Youssef-Amr-Adbdelrahman/Four-peg-tower-of-hanoi-cpp.git
cd Four-peg-tower-of-hanoi-cpp/code

# Compile
g++ -std=c++17 -O2 -o hanoi task3_hanoi.cpp

# Run
./hanoi
```

**Expected output (abbreviated):**

```
+---+--------+------+--------+
| n | T(n,4) | kopt | T(n,3) |
+---+--------+------+--------+
| 1 | 1      | 1    | 1      |
| 2 | 3      | 1    | 3      |
...
| 8 | 33     | 4    | 255    |
+---+--------+------+--------+

OPT(8,4) = 33
Can DP solve in 33 moves? YES - confirmed!

Total moves generated: 33
  Move  1:  Disk 1   A -> B
  Move  2:  Disk 2   A -> C
  ...
  Move 33:  Disk 8   A -> D
```

---

## 📈 Complexity Analysis

| Metric          | Value       |
|-----------------|-------------|
| DP build time   | O(n²)       |
| DP space        | O(n)        |
| Move generation | O(T(n,4))   |
| Moves for n=8   | **33**      |

---

## 📚 Report Highlights

The 28-page research report covers:

- Background on the classical 3-peg Tower of Hanoi
- The Frame-Stewart conjecture and its mathematical status
- Formal problem definition with state diagrams
- Full algorithm flowcharts for both D&C and DP
- Rigorous 33-move proof — all k values examined for n=8
- Complete C++ code with line-by-line commentary
- Complexity analysis with time and space proofs
- General DP table for n=1 to 12

📄 [View the full report →](report/Task3_Research_Report.pdf)

---

## 🎬 Demo Video

[![Demo Video](https://img.youtube.com/vi/8t3vKj7OVSw/maxresdefault.jpg)](https://youtu.be/8t3vKj7OVSw)

---

## 🔗 References

- Frame, J. S. (1941). *Solution to advanced problem 3918.* American Mathematical Monthly.
- Stewart, B. M. (1941). *Solution to advanced problem 3918.* American Mathematical Monthly.
- Cormen, T. H., et al. (2022). *Introduction to Algorithms* (4th ed.). MIT Press.
- Bousch, T. (2014). *La quatrième tour de Hanoï.* Bull. Belg. Math. Soc. Simon Stevin.

---

<div align="center">

**CSE245 – Advanced Algorithms and Complexity &nbsp;|&nbsp; Ain Shams University &nbsp;|&nbsp; Team 20 &nbsp;|&nbsp; Task 3**

</div>
