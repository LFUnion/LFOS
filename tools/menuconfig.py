import os
import os.path

def configure():
    files = ["./config/kconfig.py"]
    options = []

    while True:
        if len(files) < 1:
            break

        with open(files[-1], "r") as file:
            try:
                exec(file.read())
                values = eval("get_config()")
            except:
                dialog.msgbox("Broken config file: " + files[-1])
                os.system("clear")
                exit(-1)

            if values[0] == "menu":
                if values[1] == "back":
                    files.remove(files[-1])
                    continue

                files.append(values[1])
            else:
                options.append(values[1])
                files.remove(files[-1])

    return options

def mainloop():
    try:
        import dialog
        from dialog import Dialog
    except ImportError:
        print("This script requires dialog and pythondialog")
        exit(-1)

    global dialog
    dialog = Dialog(autowidgetsize=True)
    dialog.set_background_title("LFOS Configuration")
    dialog.msgbox(
        "Welcome to LFOS menuconfig\n\nPlease note that this utility is experimental, and it is recommended to configure the kernel manually using lfos_config.h")

    if os.path.isfile("config/kconfig.py") == 0:
        dialog.msgbox("Could not find config file. Please run this script with `make menuconfig`")
        os.system("clear")
        exit(-1)

    mainmenu = [
        ("Configure", "Configure the LFOS Kernel"),
        ("Build", "Build LFOS"),
        ("Exit", "Exit this configuration utility")
    ]

    while True:
        (exitcode, choice) = dialog.menu("What do you want to do?", choices=mainmenu, title="Main menu")

        if exitcode != "ok" or choice == "Exit":
            os.system("clear")
            exit(0)

        if choice == "Configure":
            options = configure()

            configfile_content = "// Generated configuration file\n#ifndef LFOS_CONFIG_H\n#define LFOS_CONFIG_H\n\n"
            for option in options:
                configfile_content += option + "\n"
            configfile_content += "\n#endif /* LFOS_CONFIG_H */\n"

            dialog.msgbox(configfile_content, title="Config preview")

            if dialog.yesno("Do you want to save your configuration?") == "ok":
                with open("./kernel/lfos_config.h", "w") as configfile:
                    configfile.truncate()
                    configfile.write(configfile_content)

        elif choice == "Build":
            dialog.msgbox("This is not yet implemented. Please use the usual Makefile.", title="Sorry")

if __name__ == "__main__":
    mainloop()