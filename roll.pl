#!/usr/bin/env perl

use strict;

# .---.
# | 6 |
# '---'
sub printsquare {
my ($d) = @_;
    print "\n.---.\n| $d |\n'---'";
}

#   .
#  / \
# / 4 \
# `---'
#   ..
#  /  \
# / 20 \
# `----'
sub printtriangle {
    my ($d) = @_;
    if ($d < 10) {
        print "\n  .\n / \\\n/ $d \\\n`---'";
    }
    else {
        print "\n  ..\n /  \\\n/ $d \\\n`----'";
    }
}

#   .
#  / \
# / 1 \
# `, ,'
#   '
#   ..
#  /  \
# / 10 \
# `,  ,'
#   ''
sub printdiamond {
    my ($d) = @_;
    if ($d < 10) {
        print "\n  .\n,' ',\n\\ $d /\n `,'";
    }
    elsif ($d < 100) {
        print "\n  ..\n /  \\\n/ $d \\\n`,  ,'\n  ''";
    }
    else {
        print "\n  .\n,' ',\n\\$d/\n `,'";
    }
}

#   .
# ,' ',
# \ 1 /
#  `-'
#   ..
# ,'  ',
# \ 12 /
#  `--'
sub printpentagon {
    my ($d) = @_;
    if ($d < 10) {
        print "\n  .\n,' ',\n\\ $d /\n `-'";
    }
    else {
        print "\n  ..\n,'  ',\n\\ $d /\n `--'";
    }
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
        $printdice = \&printtriangle;
    }
    elsif ($die == 6) {
        $printdice = \&printsquare;
    }
    elsif ($die == 8) {
        $printdice = \&printtriangle;
    }
    elsif ($die == 10) {
        $printdice = \&printdiamond;
    }
    elsif ($die == 12) {
        $printdice = \&printpentagon;
    }
    elsif ($die == 20) {
        $printdice = \&printtriangle;
    }
    elsif ($die == 100) {
        $printdice = \&printdiamond;
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
