from os import path

from . import cpp

from MarkdownPP.Modules import Include
from MarkdownPP.Transform import Transform


def read_normal_file(filename):
    with open(filename, "r") as f:
        return f.readlines()


def read_cpp_file(filename):
    return cpp.translate_cpp_file(filename)


def read_file(filename):
    if filename.endswith('.hpp') or filename.endswith('.cpp'):
        return read_cpp_file(filename)
    else:
        return read_normal_file(filename)


class CppTranslator(Include.Include):

    def include(self, match, pwd=""):
        # This code is copied directly from the MarkdownPP's project and
        # is Copyright 2015 John Reese...

        # file name is caught in group 1 if it's written with double quotes,
        # or group 2 if written with single quotes
        filename = match.group(1) or match.group(2)

        shift = int(match.group(3) or 0)

        if not path.isabs(filename):
            filename = path.join(pwd, filename)


        try:
            # ... except for this part which I've changed.
            data = read_file(filename)
            # ... back to copied code.

            # line by line, apply shift and recursively include file data
            linenum = 0
            for line in data:
                match = self.includere.search(line)
                if match:
                    dirname = path.dirname(filename)
                    data[linenum:linenum+1] = self.include(match, dirname)

                if shift:

                    titlematch = self.titlere.search(line)
                    if titlematch:
                        to_del = []
                        for _ in range(shift):
                            if data[linenum][0] == '#':
                                data[linenum] = "#" + data[linenum]
                            elif data[linenum][0] == '=':
                                data[linenum] = data[linenum].replace("=", '-')
                            elif data[linenum][0] == '-':
                                data[linenum] = '### ' + data[linenum - 1]
                                to_del.append(linenum - 1)
                        for l in to_del:
                            del data[l]

                linenum += 1

            return data

        except (IOError, OSError) as exc:
            print(exc)

        return []

