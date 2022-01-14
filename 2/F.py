import random
import sys
import re

sys.setrecursionlimit(1000000)
text = "".join(open("comments.in", "r").readlines())
sys.stdout = open("comments.out", "w")

text = re.sub("/\*.*?\*/", "", text, flags=re.MULTILINE | re.DOTALL)
text = re.sub("\{.*?\}", "", text, flags=re.MULTILINE | re.DOTALL)
text = re.sub("//[^\n]*", "", text, flags=re.MULTILINE | re.DOTALL)

print(text, end="")

sys.stdout.flush()
sys.stdout.close()
