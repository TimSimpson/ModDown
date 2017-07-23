import sys

from . import module
import MarkdownPP.main


def main():
    import MarkdownPP.Modules
    MarkdownPP.modules['include'] = module.CppTranslator
    MarkdownPP.main.main()


if __name__ == "__main__":
    main()
