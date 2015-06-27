#! /usr/bin/env python

# Reads mixed source/text markdown files and outputs HTML and/or C++ source.
# Usage:
#   ./transform.py --o-html OUT.html --o-cxx OUT.cc in.md

import argparse
import mistune
import re
import sys

parser = argparse.ArgumentParser(description = "Translate markdown pages.",
                        epilog = "At least one output file must be specified")
parser.add_argument("--o-html", metavar = "HTML", dest = "html_file",
                    help = "HTML output file name")
parser.add_argument("--o-cxx", metavar = "CXX", dest = "cxx_file",
                    help = "C++ output file name")
parser.add_argument("md_file", metavar = "MD")

def pretty_print(text, prefix, start_with_prefix = True):
    words = text.split()

    index = 0

    if start_with_prefix:
        result = prefix
    else:
        result = ""

    while index < len(words):
        column = len(prefix)

        result += words[index]
        column += len(words[index])
        index += 1

        while index < len(words) and column + 1 + len(words[index]) <= 80:
            result += " "
            result += words[index]
            column += 1 + len(words[index])
            index += 1

        result += "\n"
        if index < len(words):
            result += prefix

    return result

def camel_case(text):
    components = re.split("[ -]+", text)
    components = map(lambda s: s.capitalize(), components)
    result = "".join(components)
    result = filter(lambda c: c not in ",!:-$()?", result)
    return result

class HtmlRenderer(mistune.Renderer):
    def __init__(self):
        super(HtmlRenderer, self).__init__()
        self._definitions = {}
        self._table_of_contents = []
        self._second_level = None

    def header(self, text, level, raw = None):
        if level == 2:
            if "title" not in self._definitions:
                self._definitions["title"] = text

        if level == 3:
            anchor_name = camel_case(text)
            prefix = "<a id=\"%s\"></a>" % anchor_name

            self._second_level = []
            self._table_of_contents.append(
                                        (anchor_name, text, self._second_level))

        elif level == 4:
            anchor_text = re.search("<em>(.+)</em>", text).group(1)
            anchor_name = camel_case(anchor_text)
            prefix = "<a id=\"%s\"></a>" % anchor_name

            self._second_level.append((anchor_name, anchor_text))

        else:
            prefix = ""

        return prefix + super(HtmlRenderer, self).header(text, level, raw)

    def paragraph(self, text):
        if text.startswith("%%"):
            tokens = text[2:].split("=", 1)
            if len(tokens) == 2:
                pass
                key = tokens[0].strip()
                value = tokens[1].strip()

                self._definitions[key] = value

            return ""

        return super(HtmlRenderer, self).paragraph(text)

    def block_code(self, code, lang):
        escaped = mistune.escape(re.sub("\n*$", "", code))
        replaced = re.sub("&lt;em&gt;", "<em>", escaped)
        replaced = re.sub("&lt;/em&gt;", "</em>", replaced)

        if lang == "comment":
            start_tag = "<pre class=\"comment\">"
        else:
            start_tag = "<pre>"

        return start_tag + replaced + "</pre>"

    def definitions(self):
        toc_text = "<a id=\"contents\"></a>"
        toc_text += "<h3 class=\"contents\">Contents</h3>"
        toc_text += "<ul class=\"contents\">"

        for entry in self._table_of_contents:
            anchor, title, second_level = entry
            toc_text += "<li><a href=\"#%s\">%s</a>" % (anchor, title)

            if len(second_level) > 0:
                toc_text += "<ul>"
                for entry in second_level:
                    toc_text += "<li><a href=\"#%s\">%s</a></li>" % entry
                toc_text += "</ul>"

            toc_text += "</li>"

        toc_text += "</ul>"

        self._definitions["internal_toc"] = toc_text

        return self._definitions

def to_html(text):
    renderer = HtmlRenderer()
    html = mistune.Markdown(renderer = renderer).render(text)
    definitions = renderer.definitions()
    definitions["body"] = html
    return definitions

def clean_text(text):
    text = re.sub("<(?P<tag>[^> ]+)[^>]*>(.*?)</(?P=tag)>", "\g<2>", text)
    text = re.sub("<(?P<tag>[^> ]+)[^>]*>(.*?)</(?P=tag)>", "\g<2>", text)
    text = re.sub("&mdash;", "-", text)
    text = re.sub("\$cxx", "C++", text)
    return text

class CxxRenderer(mistune.Renderer):
    def __init__(self):
        super(CxxRenderer, self).__init__()
        self._not_in_list()
        self._not_paragraph()

    def header(self, text, level, raw = None):
        self._not_in_list()
        return self._join_paragraph() + pretty_print(text, "// ")

    def paragraph(self, text):
        if text.startswith("%%"):
            return ""

        if text == "$internal_toc":
            return ""

        self._not_in_list()
        text = clean_text(text)
        return self._join_paragraph() + pretty_print(text, "// ")

    def codespan(self, text):
        return text

    def link(self, link, title, content):
        return content

    def list(self, body, ordered = True):
        return self._join_paragraph() + body

    def list_item(self, text):
        return ("//   %i. " % self._number_list_item()) + \
               pretty_print(clean_text(text), "//      ", False)

    def block_code(self, code, lang):
        self._not_in_list()

        code = re.sub("</?em>", "", code)

        if lang == "comment":
            code = re.sub("^(.)", "// \g<1>", code, flags = re.MULTILINE)
            code = re.sub("^$", "//", code, flags = re.MULTILINE)
            return self._join_paragraph() + code + "\n"
        else:
            self._not_paragraph()
            return "\n" + code

    def hrule(self):
        self._not_in_list()
        self._not_paragraph()
        return "\n"

    def footnote_ref(self, key, index):
        return ""

    def footnotes(self, text):
        return ""

    def _not_in_list(self):
        self._list_index = None

    def _number_list_item(self):
        if self._list_index == None:
            self._list_index = 2
            return 1
        else:
            result = self._list_index
            self._list_index += 1
            return result

    def _not_paragraph(self):
        self._join = False

    def _paragraph(self):
        self._join = True

    def _join_paragraph(self):
        if self._join:
            result = "//\n"
        else:
            result = ""

        self._join = True

        return result

def main(md_file, html_file, cxx_file):
    markdown = open(md_file, "r").read()

    if html_file != None:
        html = mistune.markdown(markdown)
        open(html_file, "w").write(html)

    if cxx_file != None:
        renderer = CxxRenderer()
        source = mistune.Markdown(renderer = renderer).render(markdown)
        source = re.sub(r"\n*$", "\n", source)
        source = "// This file was generated automatically.\n\n" + source
        open(cxx_file, "w").write(source)

if __name__ == "__main__":
    arguments = parser.parse_args()
    if arguments.html_file == None and arguments.cxx_file == None:
        parser.print_help()
        sys.exit(1)

    main(arguments.md_file, arguments.html_file, arguments.cxx_file)
