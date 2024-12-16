/*
Standard CRC 32 calculations using .pkzip type crc

CRC32(123456789)=CBF43926
*/


unsigned long crc32_read(unsigned long crc)
{
    return crc ^ 0xFFFFFFFF;
};


unsigned long CRCTable[256];
bool IsInitialized = false;


void InitialiseArray()
{
    unsigned long temp;
    int j;
    unsigned long i;
    
    for (i = 0; i < 256; i++)
    {
        temp= (unsigned long)(i&0xff);
        for (j = 0; j < 8; j++) 
        {
          if (temp & 0x1)
            temp = (temp >> 1) ^ 0xEDB88320;
          else
            temp >>= 1;
        };
        CRCTable[i]=temp;
    };
};

unsigned long crc32_initialise()
{
  if (IsInitialized==false) 
  {
      InitialiseArray();
      IsInitialized = true;
  };
    return  0xFFFFFFFF;
};

unsigned long crc32_addchar(const unsigned char octet,const unsigned long crc)
{
  //unsigned long temp;
  //int j;
/*  temp = CRCTable[((crc & 0xFF) ^ octet)];

  return  (crc >> 8) ^ temp;
  */

    return (crc >> 8) ^ CRCTable[((crc & 0xFF) ^ octet)];
};



unsigned long oldcrc32_addchar(const unsigned char octet,const unsigned long crc)
{
  unsigned long temp;
  int j;

  temp = (unsigned long)((crc & 0xFF) ^ octet);

  for (j = 0; j < 8; j++) 
    {
      if (temp & 0x1)
        temp = (temp >> 1) ^ 0xEDB88320;
      else
        temp >>= 1;
    }
  return  (crc >> 8) ^ temp;
};

unsigned long test_crc32()
{
unsigned long test;
  test=crc32_initialise();
  test=crc32_addchar('1' ,test);
  test=crc32_addchar('2' ,test);
  test=crc32_addchar('3' ,test);
  test=crc32_addchar('4' ,test);
  test=crc32_addchar('5' ,test);
  test=crc32_addchar('6' ,test);
  test=crc32_addchar('7' ,test);
  test=crc32_addchar('8' ,test);
  test=crc32_addchar('9' ,test);
  return crc32_read(test);
};


