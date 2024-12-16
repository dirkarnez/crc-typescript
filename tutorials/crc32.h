//#include "crc32.h"


unsigned long crc32_initialise();

unsigned long crc32_read(unsigned long crc);

unsigned long crc32_addchar(const unsigned char octet,unsigned long crc);

unsigned long test_crc32();