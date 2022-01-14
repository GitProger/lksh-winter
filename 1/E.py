import random
import sys

sys.setrecursionlimit(1000000)
sys.stdin = open("again.in", "r")
sys.stdout = open("again.out", "w")


def eq(a, b, p):
    return a % p == b % p


def rand(l, r):
    return random.randint(l, r)


def fpow(a, x, p):
    if x == 0:
        return 1
    r = fpow(a, x // 2, p) % p
    if x % 2 == 0:
        return (r * r) % p
    else:
        return (((r * r) % p) * a) % p


def test(p, witness=-1):
    if p < 2: 
        return False
    if p <= 3: 
        return True
    if p % 2 == 0: 
        return False
        
    t = p - 1
    s = 0
    while t % 2 == 0:
        t //= 2
        s += 1

    a = witness
    if a == -1:
        a = rand(2, p - 1)
    g = fpow(a, t, p)
    
    if eq(g, 1, p) or eq(g, -1, p):
        return True
    for i in range(s - 1):
        g = (g * g) % p
        if eq(g, 1, p): 
            return False
        if eq(g, -1, p): 
            return True
    return eq(g, 1, p)


def isprime(x):
    for good in [2, 3, 5, 7, 13, 17, 23, 561]:
        if good < x and (not test(x, good)):
            return False
    for _ in range(20):
        if not test(x):
            return False
    return True


def solve():
    x = int(input())
    print("YES" if isprime(x) else "NO", flush=False)

t = int(input())
for _ in range(t):
    solve()
sys.stdout.flush()
sys.stdout.close()
