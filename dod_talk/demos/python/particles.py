"""AoS vs SoA in Python: objects, __slots__ objects, NumPy columns."""
import sys
import time
import tracemalloc

import numpy as np

N = 1_000_000
DT = 0.016


class Particle:
    def __init__(self, i):
        self.x = self.y = self.z = 0.0
        self.vx, self.vy, self.vz = float(i % 7), float(i % 5), float(i % 3)


class SlotParticle:
    __slots__ = ("x", "y", "z", "vx", "vy", "vz")

    def __init__(self, i):
        self.x = self.y = self.z = 0.0
        self.vx, self.vy, self.vz = float(i % 7), float(i % 5), float(i % 3)


def build(cls):
    tracemalloc.start()
    ps = [cls(i) for i in range(N)]
    mem = tracemalloc.get_traced_memory()[0]
    tracemalloc.stop()
    return ps, mem


def step(ps):
    for p in ps:
        p.x += p.vx * DT
        p.y += p.vy * DT
        p.z += p.vz * DT


def timed(fn, *args):
    t0 = time.perf_counter()
    fn(*args)
    return time.perf_counter() - t0


objs, mem_obj = build(Particle)
t_obj = timed(step, objs)
del objs
slots, mem_slot = build(SlotParticle)
t_slot = timed(step, slots)
del slots

tracemalloc.start()
i = np.arange(N)
x, y, z = (np.zeros(N, np.float32) for _ in range(3))
vx, vy, vz = ((i % m).astype(np.float32) for m in (7, 5, 3))
del i
mem_np = tracemalloc.get_traced_memory()[0]
tracemalloc.stop()


def step_np():
    x[:] += vx * DT
    y[:] += vy * DT
    z[:] += vz * DT


t_np = timed(step_np)

print(f"sys.getsizeof(1.0) = {sys.getsizeof(1.0)} B   (C float = 4 B)")
print(f"objects:   {t_obj * 1e3:7.1f} ms/step  {mem_obj / 2**20:6.1f} MiB")
print(f"__slots__: {t_slot * 1e3:7.1f} ms/step  {mem_slot / 2**20:6.1f} MiB")
print(f"numpy SoA: {t_np * 1e3:7.1f} ms/step  {mem_np / 2**20:6.1f} MiB"
      f"  ({t_obj / t_np:.0f}x faster, {mem_obj / mem_np:.0f}x less memory)")
