#!/usr/bin/env perl

use strict;

#   .
#  / \
# / 4 \
# `---´
sub printd4 {
    my ($d) = @_;
    print "\n  .\n / \\\n/ $d \\\n`---´\n";
}

# .---.
# | 6 |
# '---'
sub printd6 {
    my ($d) = @_;
    print "\n.---.\n| $d |\n'---'\n";
}

#  /'\
# /___\
# \ 8 /
#  \./
sub printd8 {
    my ($d) = @_;
    print "\n /'\\\n/___\\\n\\ $d /\n \\./\n";
}

#  ./\.
# //10\\
# ``--´´
sub printd10 {
    my ($d) = @_;
    printf "\n ./\\. \n//%02d\\\\\n``--´´\n", $d;
}

#  .__.
# /\__/\
# \/12\/
#  `--´
sub printd12 {
    my ($d) = @_;
    printf "\n .__. \n/\\__/\\\n\\/%02d\\/\n `--´ \n", $d;
}

#   __
#  /__\
# /\20/\
# \_\/_/
sub printd20 {
    my ($d) = @_;
    printf "\n  __  \n /__\\ \n/\\%02d/\\\n\\_\\/_/\n", $d;
}

#   .
# .´ `.
# \100/
#  `-´
sub printd100 {
    my ($d) = @_;
    printf "\n  .\n.´ `.\n\\%03d/\n `-´\n", $d;
}

sub parsearg {
    my ($arg) = @_;
    return split('d', $arg);
    #my ($cnt, $die) = split('d', $arg);
    #return ($cnt, $die);
}

sub processroll {
    my ($cnt, $die) = @_;

    my $printdice;
    if ($die == 4) {
        $printdice = \&printd4;
    }
    elsif ($die == 6) {
        $printdice = \&printd6;
    }
    elsif ($die == 8) {
        $printdice = \&printd8;
    }
    elsif ($die == 10) {
        $printdice = \&printd10;
    }
    elsif ($die == 12) {
        $printdice = \&printd12;
    }
    elsif ($die == 20) {
        $printdice = \&printd20;
    }
    elsif ($die == 100) {
        $printdice = \&printd100;
    }
    else {
        # error, not a valid dice
        return 0;
    }

    my $result = 0;
    my $sum = 0;
    for (1..$cnt) {
        $result = int(rand($die))+1;
        &$printdice($result);
        $sum += $result;
    }

    return $sum;
}

# main
my $sum = 0;
my $mods = 0;
foreach my $arg (@ARGV) {
    if ($arg =~ /d/) {
        my ($cnt, $die) = parsearg($arg);
        $sum += processroll($cnt, $die);
    }
    elsif ($arg =~ /^(-|\+)/) {
        $mods += int($arg);
    }
}

print "\nTotal modifiers: $mods\n";
$sum += $mods;
        
print "\n$sum\n";
