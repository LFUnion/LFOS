def get_config():

    choices = [
        ("PIT Frequency", "Set the PIT frequency")
    ]
    
    global dialog
    (exitcode, chosen) = dialog.menu("Scheduler configuration", choices=choices)

    file = ""
    if exitcode != "ok":
         file = "back"
    elif chosen == "PIT Frequency":
         file = "./config/scheduler/pitfreq.py"

    return ["menu", file]

def get_defaults():
    return ["menu", ["./config/scheduler/pitfreq.py"]]
