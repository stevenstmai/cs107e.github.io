#include "timer.h"
#include "uart.h"
#include "i2c.h"
#include "printf.h"
#include "string.h"

// GPIO Pins for I2C are SDA = GPIO2, SCL = GPIO3

const unsigned int RTC_ADDR = 0x68;

const char *days[] = {"", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday",
                    "Friday", "Saturday"};

struct raw_rtc_time_info {
    // bits: 7 6 5 4 3 2 1
    unsigned char seconds; // bits 6-5-4, tens, 3-0, ones
    unsigned char minutes; // bits 5-6-4, tens, 3-0, ones
    unsigned char hours; // bit 6: 12/24, 5: 10-hr or AM/PM, 4: 10-hr, 3-0, ones
    unsigned char day; // bits 2-1-0, day (1-7)
    unsigned char date; // bits 5-4, tens, 3-0, ones (1 - 31)
    unsigned char month; // bit 4: tens, 3-0, ones (1 - 12)
    unsigned char year;  // bits 7-4, tens, 3-0, ones  
};

struct time_info_t {
    unsigned int seconds; // 0 - 59
    unsigned int minutes; // 0 - 59
    unsigned int hours;   // 0 - 23
    unsigned int day; // 1 - 7
    unsigned int date; // 1 - 31
    unsigned int month; // 1 - 21
    unsigned int year; // 0 - (2^32 - 1)
};

void rtc_init() {
    // the data sheet says the following:
    // "Please note that the initial power-on state of all registers is not
    // defined. Therefore, it is important to enable the oscillator 
    // (CH bit = 0) during initial configuration."
    //
    // This likely only needs to happen when the battery has been replaced,
    // but we can do it every time as long as we save the seconds
    char data[2] = {0, 0};

    // first, read the clock
    i2c_write(RTC_ADDR, &data[0], 1);
    i2c_read(RTC_ADDR, &data[1], 1);

    // set the top bit to zero
    data[1] &= 0b01111111;

    // write it back to set
    i2c_write(RTC_ADDR, data, 2);
}

void convert_raw_time(struct raw_rtc_time_info rtc, struct time_info_t *ti) {
    ti->seconds = ((rtc.seconds & 0b01110000) >> 4) * 10 + (rtc.seconds & 0b1111);
    ti->minutes = ((rtc.minutes & 0b01110000) >> 4) * 10 + (rtc.minutes & 0b1111);
    ti->hours = ((rtc.hours & 0b00110000) >> 4) * 10 + (rtc.hours & 0b1111);
    ti->day = rtc.day;
    ti->date = ((rtc.date & 0b01110000) >> 4) * 10 + (rtc.date & 0b1111);
    ti->month = ((rtc.month & 0b01110000) >> 4) * 10 + (rtc.month & 0b1111);
    ti->year = ((rtc.year & 0b11110000) >> 4) * 10 + (rtc.year & 0b1111);
}

void set_time(int hours, int minutes, int seconds) {
    char time_details[4];
    time_details[0] = 0; // seconds register
    time_details[1] = ((seconds / 10) << 4) + (seconds % 10);
    time_details[2] = ((minutes / 10) << 4) + (minutes % 10);
    time_details[3] = ((hours / 10) << 4) + (hours % 10);
    i2c_write(RTC_ADDR, time_details, 4);
}

void set_date(int month, int date, int year) {
    // u.s. date is month/day/year
    char time_details[4];
    time_details[0] = 4; // seconds register
    time_details[1] = ((date / 10) << 4) + (date % 10);
    time_details[2] = ((month / 10) << 4) + (month % 10);
    // year is only two digits!
    year %= 100;
    time_details[3] = ((year / 10) << 4) + (year % 10);
    i2c_write(RTC_ADDR, time_details, 4);
}

void set_day(int day) { // Sunday is 1, Saturday is 7
    // day is 1-7
    char time_details[2];
    time_details[0] = 3; // day register
    time_details[1] = day;
    i2c_write(RTC_ADDR, time_details, 4);
}

void set_rtc_ram() {
    
}

void main(void) {

    timer_init();
	uart_init();

    i2c_init();
    rtc_init(); // must happen after i2c_init

    enum Clock { sec = 0, min = 1, hour = 2, day = 3 };
    char data[64];
    memset(data, 0, 64);
    struct raw_rtc_time_info raw_time_info;
    struct time_info_t time_info;
    // set_time(12, 35, 00);
    // set_day(4); // Sunday = 1, Monday = 2, etc.
    // set_date(11, 16, 2022);
    
    while (1) {
        char reg = sec;
        i2c_write(RTC_ADDR, &reg, 1);
        // first, send the register (seconds)
        
        // read response
        i2c_read(RTC_ADDR, (char *)&raw_time_info, sizeof(raw_time_info));
        convert_raw_time(raw_time_info, &time_info);
        printf("%s, %02d/%02d/%02d, %02d:%02d:%02d\n", days[time_info.day],
                time_info.month, time_info.date, time_info.year,
                time_info.hours, time_info.minutes, time_info.seconds);
        timer_delay_ms(1000);
    }
}

