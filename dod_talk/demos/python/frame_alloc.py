"""Lifetimes in Python: allocate fresh arrays every frame vs reuse a buffer."""
import time
import tracemalloc

import numpy as np

N = 2_000_000
FRAMES = 200
DT = np.float32(0.016)
pos = np.zeros(N, np.float32)
vel = np.ones(N, np.float32)


def fresh():
    global pos
    for _ in range(FRAMES):
        pos = pos + vel * DT          # 2 new arrays every frame


tmp = np.empty(N, np.float32)         # allocated once ("arena")


def reuse():
    for _ in range(FRAMES):
        np.multiply(vel, DT, out=tmp)
        np.add(pos, tmp, out=pos)     # 0 new arrays per frame


for name, fn in (("fresh arrays", fresh), ("out= reuse", reuse)):
    tracemalloc.start()
    t0 = time.perf_counter()
    fn()
    t = time.perf_counter() - t0
    peak = tracemalloc.get_traced_memory()[1]
    tracemalloc.stop()
    print(f"{name:13}: {t / FRAMES * 1e3:5.2f} ms/frame, "
          f"peak extra {peak / 2**20:5.1f} MiB")
