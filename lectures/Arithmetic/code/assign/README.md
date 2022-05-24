Example:

uint16_t x = 0xffff;
uint32_t y = x;

int16_t x = -1;
int32_t y =  x;

int16_t x =  1;
int32_t y =  x;

// sign extension
int16_t x = -1;
int32_t y =  x;

// truncation
int32_t x = 0x80000;
int16_t y = x;

// bit copy
int32_t  x = -1;
uint32_t y =  x;



