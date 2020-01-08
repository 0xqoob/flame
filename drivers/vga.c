#include <drivers/vga.h>

uint8_t horzDisp = 0;

void getResolution() {
    // set bit 0 of 0x3C2 to 0 to allow access to 0x3D4 and 0x3D5
    uint8_t bit = port_byte_in(0x3CC);
    set_bit(&bit, 0, 0);
    port_byte_out(0x3C2, bit);

    // index 0x07 stores overflow (high order bits) for vertical timings (0x06 - 0x15)
    // set bit 7 of index 0x11 of port 0x3D4 to 0
    
    // request 0x3D4 to send the contents of register 0x11 to 0x3D5
    // read the content from 0x3D5
    // set bit 7 to 0
    // write the modified value to 0x3D5
    port_byte_out(0x3D4, 0x11);
    uint8_t pbit = port_byte_in(0x3D5);
    set_bit(&pbit, 7, 0);
    port_byte_out(0x3D5, pbit);
    
    // now you have access to 0x3D4
    // request the horizontal total from 0x3D4
    port_byte_out(0x3D4, 0x00);
    horzDisp = port_byte_in(0x3D5);
    
    // reset the protect bit
    port_byte_out(0x3D4, 0x11);
    set_bit(&pbit, 7, 1);
    port_byte_out(0x3D5, pbit);
    
    // reset bit 0 in 0x3C2
    set_bit(&bit, 0, 1);
    port_byte_out(0x3C2, bit);
}
