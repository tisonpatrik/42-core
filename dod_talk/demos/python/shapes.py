"""Same shapes as c/shapes.c: class hierarchy vs one table + arrays."""
import random
import time

import numpy as np


class Shape:
    def area(self) -> float:
        raise NotImplementedError


class Square(Shape):
    def __init__(self, side):
        self.side = side

    def area(self):
        return self.side * self.side


class Rectangle(Shape):
    def __init__(self, w, h):
        self.w, self.h = w, h

    def area(self):
        return self.w * self.h


class Triangle(Shape):
    def __init__(self, b, h):
        self.b, self.h = b, h

    def area(self):
        return 0.5 * self.b * self.h


class Circle(Shape):
    def __init__(self, r):
        self.r = r

    def area(self):
        return 3.14159265 * self.r * self.r


N = 1 << 20
random.seed(42)
kind = np.empty(N, dtype=np.uint8)
w = np.empty(N, dtype=np.float32)
h = np.empty(N, dtype=np.float32)
objs = []
for i in range(N):
    k = random.randrange(4)
    a, b = 1.0 + random.randrange(10), 1.0 + random.randrange(10)
    if k in (0, 3):
        b = a
    kind[i], w[i], h[i] = k, a, b
    objs.append([Square(a), Rectangle(a, b), Triangle(a, b), Circle(a)][k])
COEF = np.array([1.0, 1.0, 0.5, 3.14159265], dtype=np.float32)

t0 = time.perf_counter()
total_obj = sum(s.area() for s in objs)
t_obj = time.perf_counter() - t0

t0 = time.perf_counter()
total_tab = float(np.sum(COEF[kind] * w * h, dtype=np.float64))
t_tab = time.perf_counter() - t0

print(f"objects + area(): {t_obj * 1e3:8.1f} ms")
print(f"table + arrays:   {t_tab * 1e3:8.1f} ms  ({t_obj / t_tab:.0f}x)")
print(f"check: {total_obj:.0f} {total_tab:.0f}")
