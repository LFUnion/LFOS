def get_config():

    choices = [
        ("Memory Management", "Configure the memory manager"),
        ("Scheduler", "Configure the multitasking scheduler")
    ]
    
    global dialog
    (exitcode, chosen) = dialog.menu("Kernel configuration", choices=choices)

    file = ""
    if exitcode != "ok":
         file = "back"
    elif chosen == "Memory Management":
         file = "./config/memory/kconfig.py"
    elif chosen == "Scheduler":
         file = "./config/scheduler/kconfig.py"

    return ["menu", file]

def get_defaults():
    return ["menu", ["./config/memory/kconfig.py", "./config/scheduler/kconfig.py"]]
