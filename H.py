import sys
import re

text = "".join(sys.stdin.readlines())

words = list(map(
    str.lower, 
    re.findall("\\b[a-zA-Z]+\\b", text)
))

ans = {}
for w in words:
    x = 0
    if ans.get(w):
        x = ans[w]
    ans[w] = x + 1

for k in sorted(ans.keys()):
    e = ""
    if ans[k] > 1:
        e = str(ans[k])
    print(k, e)


