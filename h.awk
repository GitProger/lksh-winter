#!/usr/bin/env awk
BEGIN {
    FS="[^a-zA-Z_0-9]+"
}
{
    for (i = 1; i <= NF; i++)
        if ($i ~ /^[a-zA-Z]+$/)
            a[tolower($i)]++
}
END {
    st = "sort"
    for (w in a)
        if (a[w] == 1)
            print w | st;
        else
            print w, a[w] | st
    close (st)
}
