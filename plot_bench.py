# plot_bench.py
import sys, math, argparse
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

p = argparse.ArgumentParser()
p.add_argument("csv_path")
p.add_argument("out_path")
p.add_argument("--interp-pts", type=int, default=400,
               help="dense points on log2(n) axis for smoothing (default 400)")
p.add_argument("--show-raw", action="store_true",
               help="also plot raw averages as small markers")
p.add_argument("--no-padmarks", action="store_true",
               help="hide padding markers (x)")
args = p.parse_args()

df = pd.read_csv(args.csv_path)


avg = df.groupby(["n", "algo"], as_index=False)["ms"].mean()
pivot = avg.pivot(index="n", columns="algo", values="ms").sort_index()
n_vals = pivot.index.values.astype(float)

# which algos we actually have
algos = [a for a in ["naive", "recursive", "strassen"] if a in pivot.columns]

plt.figure(figsize=(9,5.5))

if args.show_raw:
    for algo in algos:
        plt.plot(pivot.index, pivot[algo],
                 linestyle="none", marker="o", markersize=3,
                 alpha=0.6, label=f"{algo} (avg)")


log2n = np.log2(n_vals)
grid = np.linspace(log2n.min(), log2n.max(), args.interp_pts)
n_dense = 2.0 ** grid

colors = {
    "naive":     "#d62728",  
    "recursive": "#9467bd",  
    "strassen":  "#2ca02c",  
}

for algo in algos:
    y = pivot[algo].values.astype(float)

    y_interp = np.interp(grid, log2n, np.log10(y))
    y_dense  = 10 ** y_interp
    plt.plot(n_dense, y_dense, linewidth=2.0, color=colors.get(algo, None), label=algo)


if not args.no_padmarks and "padded_n" in df.columns:
    for algo, mcolor in [("recursive", "#9467bd"), ("strassen", "#2ca02c")]:
        sub = df[df["algo"] == algo]
        if sub.empty:
            continue

        pad = (sub.groupby("n", as_index=False)["padded_n"].max())
        pad["padded"] = pad["padded_n"] > pad["n"]
        pad_ns = pad.loc[pad["padded"], "n"].values

        y_at = pivot[algo].reindex(pad_ns).dropna()
        if len(y_at):
            plt.scatter(y_at.index, y_at.values, marker="x",
                        s=35, linewidths=1.2, color=mcolor, alpha=0.7,
                        label=f"{algo}: padded→2^k")


plt.xlabel("Matrix size n")
plt.ylabel("Average time (ms)")
plt.title("Matrix Multiplication Runtimes (avg over trials)")

plt.grid(True, which="both", linestyle="--", alpha=0.25)
plt.xscale("log", base=2)
plt.yscale("log")


nmin, nmax = int(pivot.index.min()), int(pivot.index.max())
if nmin > 0:
    p0 = int(math.floor(math.log2(nmin)))
    p1 = int(math.ceil(math.log2(nmax)))
    xticks = [2**k for k in range(p0, p1+1)]
    plt.xticks(xticks, [fr"$2^{k}$" for k in range(p0, p1+1)])

    for x in xticks:
        plt.axvline(x=x, color="gray", alpha=0.10, linewidth=1)


plt.legend(frameon=True, framealpha=0.9, fontsize=9, loc="upper left")
plt.tight_layout()
plt.savefig(args.out_path, dpi=220)
print(f"Plot saved to {args.out_path}")
