def get_config():
    
    global dialog
    (exitcode, frequency) = dialog.inputbox("Set the PIT frequency", init="500")

    if frequency == "":
        frequency = "500"

    return ["option", {"pitfreq":"#define PIT_FREQUENCY "+frequency}]

def get_defaults():
    return ["option", {"pitfreq":"#define PIT_FREQUENCY 500"}]
