import csv
import os
import statistics
import matplotlib.pyplot as plt

RESULTS_DIR = "results"
SUMMARY_FILE = os.path.join(RESULTS_DIR, "benchmark.csv")
OUTPUT_DIR = os.path.join(RESULTS_DIR, "plots")

os.makedirs(OUTPUT_DIR, exist_ok=True)

# Read CSV summary
with open(SUMMARY_FILE, newline="") as file:
    rows = list(csv.DictReader(file))

def get_time(mode, threads):
    for row in rows:
        if row["Mode"] == mode and int(row["Threads"]) == threads:
            return float(row["TimeMs"])
    raise ValueError(f"Missing data: {mode}, {threads} threads")

# Use median timings for the main comparison
sequential = get_time("Sequential Median", 1)
threads = [1, 2, 4, 8]

parallel = [
    get_time("Parallel Median", count)
    for count in threads
]

speedups = [sequential / time for time in parallel]
efficiencies = [
    speedup / count * 100
    for speedup, count in zip(speedups, threads)
]

# 1. Execution time comparison
plt.figure(figsize=(9, 5))
plt.bar(
    ["Sequential"] + [f"{t} threads" for t in threads],
    [sequential] + parallel
)
plt.ylabel("Execution Time (ms)")
plt.title("Sequential vs Parallel Execution Time")
plt.tight_layout()
plt.savefig(os.path.join(OUTPUT_DIR, "execution_time.png"), dpi=200)
plt.close()

# 2. Speedup
plt.figure(figsize=(8, 5))
plt.plot(threads, speedups, marker="o", label="Measured speedup")
plt.plot(threads, threads, linestyle="--", label="Ideal speedup")
plt.xlabel("Number of Threads")
plt.ylabel("Speedup (x)")
plt.title("Parallel Speedup")
plt.xticks(threads)
plt.legend()
plt.tight_layout()
plt.savefig(os.path.join(OUTPUT_DIR, "speedup.png"), dpi=200)
plt.close()

# 3. Parallel efficiency
plt.figure(figsize=(8, 5))
plt.plot(threads, efficiencies, marker="o")
plt.axhline(y=100, linestyle="--", label="Ideal efficiency")
plt.xlabel("Number of Threads")
plt.ylabel("Efficiency (%)")
plt.title("Parallel Efficiency")
plt.xticks(threads)
plt.legend()
plt.tight_layout()
plt.savefig(os.path.join(OUTPUT_DIR, "efficiency.png"), dpi=200)
plt.close()

print("Graphs saved in results/plots/")
print(f"Sequential median: {sequential:.3f} ms")

for count, time, speedup, efficiency in zip(
    threads, parallel, speedups, efficiencies
):
    print(
        f"{count} threads: {time:.3f} ms | "
        f"Speedup: {speedup:.2f}x | "
        f"Efficiency: {efficiency:.1f}%"
    )
