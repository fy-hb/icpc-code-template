import yaml
import hashlib
import re


def escape(s: str):
    return s.replace(r"_", r"\_")


def gethash(s: str, lang: str):
    if lang == "cpp":
        s = s.split("//")[0]
    elif lang == "py":
        s = s.split("#")[0]
    s = re.sub(r"\s", r"", s)
    return hashlib.md5(s.encode("UTF-8")).hexdigest()[:4]


if __name__ == "__main__":
    with open("sections.yaml", "r", encoding="UTF-8") as file:
        contents = yaml.safe_load(file)

    with open("template/header.tex", "r", encoding="UTF-8") as file:
        print(file.read(), end="")

    for section in contents:
        print("\\section{{{0}}}".format(escape(section["name"])))
        print()

        folder_name = section["folder"]

        for part in section["subs"]:
            print("\\subsection{{{0}}}".format(escape(part["name"])))

            if isinstance(part["file"], list):
                lists = part["file"]
            else:
                lists = [part["file"]]

            for file_name in lists:
                lang = file_name.split(".")[-1]
                with open(f"code/{folder_name}/{file_name}", "r", encoding="UTF-8") as file:
                    code = file.read()
                hashes = []

                for index, line in enumerate(code.split("\n")):
                    if lang == "tex":
                        hashes.append(index + 1)
                    else:
                        hashes.append(gethash(line, lang))

                print()
                for index, hash in enumerate(hashes, 1):
                    print("\\DefineCustomLabel{{{0}}}{{{1}}}".format(index, hash))
                print()

                if lang != "tex":
                    print("\\begin{{minted}}{{{0}}}".format(lang))

                print(code, end="")

                if lang != "tex":
                    print("\\end{{minted}}".format())

                print()

    with open("template/ender.tex", "r", encoding="UTF-8") as file:
        print(file.read(), end="")
