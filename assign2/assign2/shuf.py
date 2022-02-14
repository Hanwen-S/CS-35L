#!/usr/bin/python
import random
import argparse
import sys

class shuf:
    def __init__(self, filename):
        f = open(filename, 'r')
        self.lines = f.readlines()
        f.close()
    def return_lines(self):
        return self.lines

def random_lines(lines):
    return random.sample(lines, len(lines))

def choose_line(lines):
    return random.choice(lines)

def lo_hi(lo_hi):
    (lo, hi) = lo_hi.split("-")
    return (int(lo), int(hi))

def main():
#     version_msg = "%prog 2.0"
    usage_msg = """Usage: shuf [OPTION]... [FILE]
  or:  shuf -e [OPTION]... [ARG]...
  or:  shuf -i LO-HI [OPTION]...
Write a random permutation of the input lines to standard output.

Mandatory arguments to long options are mandatory for short options too."""

    parser = argparse.ArgumentParser(usage = usage_msg)
    parser.add_argument("-e","--echo", action="store_true",
                                    help="treat each ARG as an input line")
    parser.add_argument("-i","--input-range", metavar="LO-HI",
                                    help="treat each number LO through HI as an input line")
    parser.add_argument("-n","--head-count", metavar="COUNT", action = "store", type=int,
                                    help="output at most COUNT lines")
    parser.add_argument("-r", "--repeat", action = "store_true",
                                    help = "output lines can be repeated")
    parser.add_argument("-", "--read-stdin", action="store_true",
                                    help="read standard input file")

    lines = []

    try:
        options, args = parser.parse_known_args(sys.argv[1:])
    except Exception as err:
        sys.stdout.write(str(err))
        exit(0)

    if options.input_range:
        lo, hi = lo_hi(options.input_range)
        lines = [str(x) for x in range(lo, hi + 1)]
    elif options.echo:
        lines = args
    elif (len(args) > 0):
        for arg in args:
            if arg[0] == '-':
                sys.stdout.write("shuf: invalid option -- " + arg[1] + "\nTry 'shuf --help' for more information.\n")
                exit(0)
        try:
            input_file = args[0]
            generator = shuf(input_file)
            lines = generator.return_lines()
        except Exception as err:
            exit(0)
    elif (len(args) == 0):
        while (True):
            try:
                line = input()
                lines.append(line + '\n')
            except EOFError:
                break
    else:
        exit(0)

    try:
        count = options.head_count
    except:
        count = len(lines)

    while (options.repeat and count != 0):
        sys.stdout.write(choose_line(lines).rstrip("\n") + "\n")
        if (options.head_count):
            count -= 1
    for line in random_lines(lines)[:count]:
        sys.stdout.write(line.rstrip("\n") + "\n")

if __name__ == "__main__":
    main()
