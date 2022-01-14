import random
import sys


sys.setrecursionlimit(1000000)
sys.stdin = open("for.in", "r")
sys.stdout = open("for.out", "w")


def solve():
    fur, var, aus, rang = input().split()
    r = rang[6:-2]
    print("for (int " + var + " = 0; " + var + " < " + r + "; ++" + var + ") {")

t = 1
for _ in range(t):
    solve()
sys.stdout.flush()
sys.stdout.close()
