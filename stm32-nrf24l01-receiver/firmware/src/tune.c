#include <stdint.h>
#include "tones.h"
#include "esc.h"

int melody[] = {
    NOTE_E7, NOTE_E7, 0, NOTE_E7, 
    0, NOTE_C7, NOTE_E7, 0,
    NOTE_G7, 0, 0,  0,
//    NOTE_G6, 0, 0, 0, 
};

int tempo[] = {
    12, 12, 12, 12, 
    12, 12, 12, 12,
    12, 12, 12, 12,
//    12, 12, 12, 12, 
};

extern void delay_us(uint32_t microseconds);

void start_sound(void)
{
    for (int thisNote = 0; thisNote < sizeof(melody) / sizeof(melody[0]); thisNote++) {

        // to calculate the note duration, take one second
        // divided by the note type.
        //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
        int noteDuration = 1000/tempo[thisNote];

        pwm_beep(melody[thisNote]);
        delay_us(noteDuration * 1000);
        pwm_beep(0);

        // to distinguish the notes, set a minimum time between them.
        // the note's duration + 30% seems to work well:
        int pauseBetweenNotes = noteDuration * 1;
        delay_us(pauseBetweenNotes * 1000);
   }
}

void bat_beep(int cnt)
{
    while (cnt) {
        pwm_beep(NOTE_A7);
        delay_us(150000);
        pwm_beep(0);
        delay_us(400000);

        cnt--;
    }
}

void alarm_beep(void)
{
    int cnt = 10;

    while (cnt) {
        pwm_beep(NOTE_C8);
        delay_us(150000);
        pwm_beep(NOTE_A7);
        delay_us(150000);

        cnt--;
    }

    pwm_beep(0);
}


void long_beep(void)
{
    pwm_beep(NOTE_A7);
    delay_us(1000000);
    pwm_beep(0);
}
