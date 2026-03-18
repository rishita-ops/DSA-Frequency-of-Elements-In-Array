# DSA — Find the Frequency of a Number in an Array

A clean, focused C++ implementation that counts how many times a specific number appears in an array — its **frequency**. This is the most fundamental frequency operation in DSA: a single linear scan with a counter. It is the atomic primitive that underpins duplicate detection, mode finding, frequency-based sorting, and hash map construction. Every more complex frequency problem reduces to this core idea applied efficiently across multiple elements.

---

## Problem Statement

Given an array of `n` integers and a target number `num`, count how many times `num` appears in the array.

**Example Input:**
```
Enter the size of array: 8
Enter the array elements: 3 7 2 7 5 7 1 4
Enter the number to find frequency: 7
```

**Example Output:**
```
Frequency of 7 is: 3
```

---

## The Code

```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cout << "Enter the size of array: ";
    cin >> n;

    int arr[n];
    cout << "Enter the array elements: ";
    for(int i = 0; i < n; i++)
        cin >> arr[i];

    int num;
    cout << "Enter the number to find frequency: ";
    cin >> num;

    int count = 0;
    for(int i = 0; i < n; i++)
    {
        if(arr[i] == num)
            count++;
    }

    cout << "Frequency of " << num << " is: " << count << endl;

    return 0;
}
```

---

## How It Works

1. **Read input** — `n` elements are stored in `arr[]`, then the target `num` is read.
2. **Initialize counter** — `count = 0` assumes the number appears zero times until proven otherwise.
3. **Linear scan** — every element is compared to `num`. Each match increments `count`.
4. **Output** — `count` holds the exact number of occurrences regardless of whether `num` was found zero, one, or many times.

The entire algorithm is four lines. There is no early exit — the full array is always scanned, which is necessary to guarantee correctness since `num` may appear at any position including the last.

---

## Algorithm (Pseudocode)

```
read n
read arr[0..n-1]
read num

count ← 0

for i from 0 to n-1:
    if arr[i] == num:
        count ← count + 1

print count
```

---

## Dry Run

**Input:** `arr[] = {3, 7, 2, 7, 5, 7, 1, 4}`, `num = 7`, `n = 8`

| `i` | `arr[i]` | `arr[i] == 7`? | `count` |
|-----|----------|----------------|---------|
| 0   | 3        | ❌             | 0       |
| 1   | 7        | ✅             | 1       |
| 2   | 2        | ❌             | 1       |
| 3   | 7        | ✅             | 2       |
| 4   | 5        | ❌             | 2       |
| 5   | 7        | ✅             | 3       |
| 6   | 1        | ❌             | 3       |
| 7   | 4        | ❌             | 3       |

**Output:** `Frequency of 7 is: 3` ✅

---

## Complexity Analysis

| Metric | Complexity |
|--------|------------|
| Time   | **O(n)** — every element visited exactly once; no early exit |
| Space  | **O(n)** — array of size `n` stored in memory; O(1) auxiliary — only `count` maintained |

> **No early exit:** Unlike search problems, frequency counting cannot stop early — the number may appear multiple times at any position, so the entire array must be scanned. Stopping at the first match would give frequency `1` for any present element.

---

## The Zero-Frequency Case — Correct by Default

If `num` is not present in the array, the `if` condition never triggers and `count` remains at its initialized value of `0`. The output correctly states:

```
Frequency of 9 is: 0
```

No special case, no error, no branch — `count = 0` initialization handles absence implicitly and correctly. This is the **pessimistic initialization** pattern: assume the count is zero and let matches prove otherwise.

---

## Single-Query vs Full Frequency Table

This program answers a **single frequency query** — one specific `num` at a time. To find frequencies of all distinct elements simultaneously, a **hash map** builds the complete frequency table in one pass:

```cpp
#include <iostream>
#include <unordered_map>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int arr[n];
    for(int i = 0; i < n; i++) cin >> arr[i];

    unordered_map<int, int> freq;
    for(int i = 0; i < n; i++)
        freq[arr[i]]++;

    for(auto& pair : freq)
        cout << pair.first << " appears " << pair.second << " times\n";
}
```

| Approach | Time | Space | Answers |
|----------|------|-------|---------|
| Linear scan (this repo) | O(n) per query | O(1) auxiliary | One element |
| Hash map | O(n) once | O(k) — k distinct values | All elements |

For a **single query**, the linear scan is optimal — O(n) time, O(1) space, no overhead. For **multiple queries on the same array**, building a hash map once and answering each query in O(1) is the correct approach.

---

## This Program in the Context of This Series

This is the **atomic frequency primitive** that two earlier programs in this series implemented inefficiently as nested O(n²) loops:

| Earlier Program | What it did | How it counted frequency |
|-----------------|-------------|-------------------------|
| **Find Duplicates** | Printed elements with count > 1 | Inner loop scanned full array for each outer element — O(n²) |
| **Find Unique Elements** | Printed elements with count == 1 | Inner loop scanned full array for each outer element — O(n²) |
| **This program** | Reports exact frequency of one element | Single linear scan — O(n) |

The nested loop approach in those programs was essentially calling this linear scan `n` times — once for each outer element. Extracting the frequency query into its cleanest standalone form, as done here, is the foundation for understanding why hash maps reduce the combined cost from O(n²) to O(n).

---

## Edge Cases

| Scenario | Behavior |
|----------|----------|
| `num` not in array | `count` stays `0` → `"Frequency of X is: 0"` ✅ |
| `num` appears once | `count = 1` ✅ |
| `num` appears at every position | `count = n` ✅ |
| `num` is the first element only | `count = 1` — full scan confirms no other occurrences ✅ |
| `num` is the last element only | `count = 1` — correctly found at the end ✅ |
| `n = 1`, element matches | `count = 1` ✅ |
| `n = 1`, element doesn't match | `count = 0` ✅ |
| All elements identical, `num` matches | `count = n` ✅ |
| All elements identical, `num` doesn't match | `count = 0` ✅ |
| `n = 0` | ⚠️ VLA of size 0 — loop skipped, `count = 0` printed — undefined behavior on VLA |

---

## A Note on `#include <bits/stdc++.h>` and VLA

**`bits/stdc++.h`:** The only header actually needed is `#include <iostream>`. The GCC-specific umbrella header compiles correctly but is not portable and not recommended in production or product-company interview code.

**`int arr[n]`:** Variable Length Array — a GCC/C99 extension, not standard C++. For portable code, use `std::vector<int> arr(n)`.

---

## Repository Structure

```
DSA-Frequency/
│
├── frequency.cpp       # Main C++ implementation
└── README.md           # Project documentation
```

---

## How to Compile and Run

**Prerequisites:** GCC / G++

```bash
# Clone the repository
git clone https://github.com/rishita-ops/DSA-Frequency.git
cd DSA-Frequency

# Compile
g++ frequency.cpp -o frequency

# Run
./frequency
```

**On Windows:**
```bash
g++ frequency.cpp -o frequency.exe
frequency.exe
```

---

## Key Concepts Covered

- **Frequency counting** — the fundamental operation of counting element occurrences
- **Pessimistic initialization** — `count = 0` correctly handles the zero-occurrence case without a special branch
- **No early exit** — frequency requires scanning the full array; contrast with search which stops at first match
- **Single-query vs full frequency table** — when a linear scan suffices vs when a hash map is needed
- **Linear scan as the O(n) primitive** — understanding how O(n²) duplicate/unique programs decompose into this
- **VLA (`int arr[n]`)** — GCC extension; prefer `std::vector<int>` for portability
- **`bits/stdc++.h`** — only `<iostream>` needed here

---

## Why This Problem Matters in DSA

| Problem / Concept | Connection |
|-------------------|------------|
| **Find Duplicates** (this series) | Uses nested frequency counts — this is the inner O(n) scan made explicit |
| **Find Unique Elements** (this series) | Same — frequency == 1 is the uniqueness condition |
| **LeetCode #169** (Majority Element) | Find element with frequency > n/2 — frequency counting is the brute-force base |
| **LeetCode #347** (Top K Frequent Elements) | Build full frequency table (hash map), find top k — extends this primitive |
| **LeetCode #1** (Two Sum) | Hash map tracks frequencies/presence of seen elements — same scan logic |
| **Counting Sort** | Builds a frequency array for all values in range — this scan applied to every element |
| **Mode of an array** | The element with the highest frequency — run this query for each distinct value |
| **Frequency-based sorting** | Sort by how often elements appear — requires this count for each element |
| **Anagram detection** (this series) | Character frequency comparison — this exact operation on char arrays |

Frequency counting is not just one problem — it is the fundamental operation from which a large family of array, string, and sorting problems are built. Understanding it in its simplest form here makes every hash-map-based frequency solution intuitive rather than mechanical.

---

## Contributing

Contributions are welcome. Consider adding:
- A version that finds frequencies of **all distinct elements** using `unordered_map`
- A version that finds the **mode** (most frequent element) in one pass
- A version that answers **multiple frequency queries** on the same array efficiently
- Input validation for `n = 0`
- Implementations in Python, Java, or JavaScript

```bash
git checkout -b feature/your-feature
git commit -m "Add: your feature description"
git push origin feature/your-feature
# Then open a Pull Request
```

---

## License

This project is open-source and available under the [MIT License](LICENSE).

---

*Part of a structured DSA practice series — fundamentals, done right.*
