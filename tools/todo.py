# This scripts creates two TODO-lists out of one document+

def mktxt(content):
    finished = ""
    finished += """| TODO list               | Marks                    |\n| (Highest priority first)| F = stone3311, L = meles5|\n|-------------------------|--------------------------|\n\n"""

    iterator = 1

    for line in content:
        if ":" in line:
                line = line.split(":")
                finished += str(iterator) + ". " + line[0] + " " + line[1]
                iterator += 1

    return finished


def mkmd(content):
    finished = ""
    finished += "## Not implemented yet:\n\n| To implement                  | Responsible user          |\n| ----------------------------- | ------------------------- |"
    finished += "\n"

    lUrl = """<img alt="meles5" title="meles5" class="avatar" src="https://avatars1.githubusercontent.com/u/10196097?v=3&s=460" height="20" width="20">"""
    fUrl = """<img alt="stone3311" title="stone3311" class="avatar" src="https://avatars3.githubusercontent.com/u/9110659?v=3&amp;s=40" height="20" width="20">"""
    lfUrl = """<img alt="meles5" title="meles5" class="avatar" src="https://avatars1.githubusercontent.com/u/10196097?v=3&s=460" height="20" width="20"> <img alt="stone3311" title="stone3311" class="avatar" src="https://avatars3.githubusercontent.com/u/9110659?v=3&amp;s=40" height="20" width="20">"""
    
    for line in content:
        if ":" in line:
            line = line.split(":")
            imgUrl = ""
            
            if line[1] == "meles5" or line[1] == "meles5\n":
                imgUrl = lUrl
            elif line[1] == "stone3311" or line[1] == "stone3311\n":
                imgUrl = fUrl
            elif line[1] == "lfunion" or line [1] == "lfunion\n":
                imgUrl = lfUrl

            finished += "| " + line[0] + " | " + imgUrl + " |\n"
            

    return finished
    

content = ""
with open("todo.template", "r") as file:
    content = file.readlines()

with open("TODO.txt", "w") as txt:
    txt.write(mktxt(content))

with open("TODO.md", "w") as md:
    md.write(mkmd(content))
