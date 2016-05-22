#include "pic.h"

#include "stdint.h"
#include "portio.h"

#define PIC_MASTER_CMD  0x20
#define PIC_MASTER_DATA 0x21
#define PIC_SLAVE_CMD   0xA0
#define PIC_SLAVE_DATA  0xA1

#define PIC_MASTER_OFFSET 0x20
#define PIC_SLAVE_OFFSET  0x28

void pic_init() {
    unsigned char imr_master, imr_slave;
    
    imr_master = inb(PIC_MASTER_DATA);
    imr_slave  = inb(PIC_SLAVE_DATA);
    
    outb(PIC_MASTER_CMD, 0x11); // Initialize master
    outb(PIC_SLAVE_CMD, 0x11);  // Initialize slave
    
    outb(PIC_MASTER_DATA, PIC_MASTER_OFFSET); // Master offset
    outb(PIC_SLAVE_DATA, PIC_SLAVE_OFFSET);   // Slave offset
    
    outb(PIC_MASTER_DATA, 4); // Set cascading 
    outb(PIC_SLAVE_DATA, 2);  //  mode
    
    outb(PIC_MASTER_DATA, 0x1); // Set 8086
    outb(PIC_SLAVE_DATA, 0x1);  //  mode
    
    outb(PIC_MASTER_DATA, imr_master); // Restore
    outb(PIC_SLAVE_DATA, imr_slave);   //  Interrupt Mask Register
}
