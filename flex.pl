#!/usr/bin/env perl

$text = `convert flex.png txt:- | cut -d " " -f 4 | uniq -c`;
@lines = split "\n", $text;
%colors = ();
for $line (@lines) {
    ($shift, $cnt, $col) = split /\s+/, $line;
    $colors{$col} += $cnt;
}

for $c (keys %colors) {
    print "$c ${colors{$c}}\n";
}
