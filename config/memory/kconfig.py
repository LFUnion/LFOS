def get_config():

    choices = [
        ("MM Type", "Choose a memory manager")
    ]
    
    global dialog
    (exitcode, chosen) = dialog.menu("Memory manager configuration", choices=choices)

    file = ""
    if exitcode != "ok":
         file = "back"
    elif chosen == "MM Type":
         file = "./config/memory/mmtype.py"

    return ["menu", file]

def get_defaults():
    return ["menu", ["./config/memory/mmtype.py"]]