#include "keyboard.h"
#include "driver_api.h"


struct driver_data_keyboard{
    struct driver_data datai;
    union function_data pfunc[7];
    
};    


// PS/2 controller port: 0x64
// Keyboard port:      0x60



uint8_t kbd_send(uint8_t command) {
    int resend = 1;
    while(resend == 1) {
        outb(0x60, command);
        uint8_t ret = inb(0x60);
        if(ret == 0xFE) {
            resend = 1;
            continue;
        } else {
            if(ret == 0xFA) {
                resend = 0;
                return 0xFA;
            } else {
                resend = 0;
                return ret;
            }
        }
    }
    printw("[EE] EXCEPTION: Reached end of keyboard output buffer ");
    return 0;
}

uint8_t kbd_pull_key() {
    while (((inb(0x64) >> 0)  & 0x01) == 0) {} // Wait until there is something in the buffer
    return inb(0x60); // Read the buffer
}

int kbd_reset() {
    uint8_t resp = kbd_send(0xFF); // Sending reset command
    if(resp == 0xFA) { // 0xFA = Reset done
        return 1;
    } else {
        return 0;
    }
}

int kbd_flush_buffer() {
    outb(0x64, 0xAD); // Disable PS/2 (1)
    while ((inb(0x64) >> 0)  & 0x01) {
        inb(0x60);    // Flush   buffer
    }
    outb(0x64, 0xAE); // Enable  PS/2 (1)
    return 1;
}

int kbd_init() {
    if(kbd_reset() == 0) {
    return 0; // Reset failed
    }
    kbd_send(0xF6); // Load defaults
    return 1;
}

int kbd_detect() {
    outb(0x60, 0xEE); // Sending echo command
    uint8_t response = inb(0x60); // Waiting for response
    if(response == 0xEE || response == 0xFE) {
        return 1;
    } else {
        return 0;
    }
}

char kbd_pull_char() {
    uint8_t scancode = kbd_pull_key();

    if          (scancode == 0x02) {
    return '1';
    } else if (scancode == 0x03) {
    return '2';
    } else if (scancode == 0x04) {
    return '3';
    } else if (scancode == 0x05) {
    return '4';
    } else if (scancode == 0x06) {
    return '5';
    } else if (scancode == 0x07) {
    return '6';
    } else if (scancode == 0x08) {
    return '7';
    } else if (scancode == 0x09) {
    return '8';
    } else if (scancode == 0x0A) {
    return '9';
    } else if (scancode == 0x0B) {
    return '0';
    } else if (scancode == 0x0C) {
    return '-';
    } else if (scancode == 0x0D) {
    return '=';
    } else if (scancode == 0x0E) {
    return '\b';
    } else if (scancode == 0x0F) {
    return '\t';
    } else if (scancode == 0x10) {
    return 'Q';
    } else if (scancode == 0x11) {
    return 'W';
    } else if (scancode == 0x12) {
    return 'E';
    } else if (scancode == 0x13) {
    return 'R';
    } else if (scancode == 0x14) {
    return 'T';
    } else if (scancode == 0x15) {
    return 'Y';
    } else if (scancode == 0x16) {
    return 'U';
    } else if (scancode == 0x17) {
    return 'I';
    } else if (scancode == 0x18) {
    return 'O';
    } else if (scancode == 0x19) {
    return 'P';
    } else if (scancode == 0x1A) {
    return '[';
    } else if (scancode == 0x1B) {
    return ']';
    } else if (scancode == 0x1C) {
    return '\n';
    } else if (scancode == 0x1E) {
    return 'A';
    } else if (scancode == 0x1F) {
    return 'S';
    } else if (scancode == 0x20) {
    return 'D';
    } else if (scancode == 0x21) {
    return 'F';
    } else if (scancode == 0x22) {
    return 'G';
    } else if (scancode == 0x23) {
    return 'H';
    } else if (scancode == 0x24) {
    return 'J';
    } else if (scancode == 0x25) {
    return 'K';
    } else if (scancode == 0x26) {
    return 'L';
    } else if (scancode == 0x27) {
    return ';';
    } else if (scancode == 0x2C) {
    return 'Z';
    } else if (scancode == 0x2D) {
    return 'X';
    } else if (scancode == 0x2E) {
    return 'C';
    } else if (scancode == 0x2F) {
    return 'V';
    } else if (scancode == 0x30) {
    return 'B';
    } else if (scancode == 0x31) {
    return 'N';
    } else if (scancode == 0x32) {
    return 'M';
    } else if (scancode == 0x39) {
    return ' ';
    } else {
    return (char)0;
    }

}


// Keyboard API

const struct driver_data_keyboard key_api = 
{
    .datai.driver_number=KEYBOARD,
    .datai.number_of_functions=7,
    .datai.driver_priority=1,
    .datai.driver_description="Keyboard Driver: -communication with keyboard\n-scan of input and interpretation",
    .pfunc[0].func_8_8 = &kbd_send,
    .pfunc[1].func_8 = &kbd_pull_key,
    .pfunc[2].func_i = &kbd_reset,
    .pfunc[3].func_i = &kbd_flush_buffer,
    .pfunc[4].func_i = &kbd_init,
    .pfunc[5].func_i = &kbd_detect,
    .pfunc[6].func_c = &kbd_pull_char

};

void keyboard_send() {
    print_raw("Number of functions: ");
    printf(stringFromInt(key_api.datai.number_of_functions));
    print_raw("Priority: ");
    printf(stringFromInt(key_api.datai.driver_priority));
    printf(key_api.datai.driver_description);
}


void keyboard_use(const int func){
    ;
    
    
}
