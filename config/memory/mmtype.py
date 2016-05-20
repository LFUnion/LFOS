def get_config():

    choices = [
        ("Segmenting memory manager", "Can allocate and free segments of memory", True),
        ("Watermark memory manager", "Can only allocate new memory, freeing is impossible", False)
    ]
    
    global dialog
    (exitcode, chosen) = dialog.radiolist("Choose a memory manager", choices=choices)

    option = ""
    if exitcode != "ok":
         option = ""
    elif chosen == "Segmenting memory manager":
         option = "#define MM_SEGMENTATION"
    elif chosen == "Watermark memory manager":
         option = "#define MM_WATERMARK"

    return ["option", option]
