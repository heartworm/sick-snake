/* File: button_solution.c
 * Description: C program for the ATMEL AVR microcontroller (ATmega32 chip)
 * Turn on Teensy LED with button

 * Teensy PewPew

 * Includes (pretty much compulsory for using the Teensy this semester)
 * 	- avr/io.h: port and pin definitions (i.e. DDRB, PORTB, PB1, etc)
 *
 *	- cpu_speed.h: macros for forcing the CPU speed to 8MHz (nothing else should ever be used!)
 */



// AVR header file for all registers/pins
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "cpu_speed.h"
#include "lcd.h"

#include "interface.h"
#include "main.h"

volatile uint8_t bouncer[6] = {0,0,0,0,0,0};
volatile uint8_t buttonState = 0x00;

void set_ddr();
void set_interrupts();
volatile int x = 0;

int main(void){
    
    // Set the CPU speed to 8MHz (you must also be compiling at 8MHz)
    set_clock_speed(CPU_8MHz);
    
	set_ddr();
	set_interrupts();
	PORTC |= 1<<7;
	
	lcd_init(LCD_DEFAULT_CONTRAST);
	clear_screen();
	draw_string(25, 0, "Shravan");
	draw_string(35, 9, "Lal");
	draw_string(23, 18, "n9286675");
	show_screen();
	_delay_ms(2000);
	
	initGame(1);
	
    while(1){      
		handleButton(buttonState);
		stepGame();
	
		clear_screen();
		drawGame();
		show_screen();
		_delay_ms(100 + ADC/2);
	}
	
	return 0;
}

void set_ddr() {
	DDRD = 0x00;
	DDRF = 0x00;
	DDRB = 0x00;
	DDRC |= (1<<7); //LCD backlight
	//vcc adc ref
	ADMUX = (1<<REFS0);
	///128 prescale for adc, autotriggering enabled, start conversion
    ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADATE)|(1<<ADSC);

}

void resetButtons() {
	buttonState = 0;
}

void flashDisplay() {
	DDRC &= ~(1<<7);
	_delay_ms(200);
	DDRC |= (1<<7);
	_delay_ms(200);
	DDRC &= ~(1<<7);
	_delay_ms(200);
	DDRC |= (1<<7);
}

void set_interrupts() {
	cli();
	//TCCR0B &= ~((1<<WGM02));
	TCCR0B |= 1<<CS02; //Prescaler 256
	//TCCR0B &= ~((1<<CS01) | (1<<CS00));
	TIFR0 = 1<<TOV0; //clear overflow flag
	TIMSK0 |= 1<<TOIE0; //Enable overflow interrupt
	sei();
}

ISR(TIMER0_OVF_vect) {
	bouncer[OFFHATU] = bouncer[OFFHATU] << 1 | ((PIND >> 1) & 1);
	bouncer[OFFHATD] = bouncer[OFFHATD] << 1 | ((PINB >> 7) & 1);
	bouncer[OFFHATL] = bouncer[OFFHATL] << 1 | ((PINB >> 1) & 1);
	bouncer[OFFHATR] = bouncer[OFFHATR] << 1 | ((PIND >> 0) & 1);
	bouncer[OFFBUTL] = bouncer[OFFBUTL] << 1 | ((PINF >> 6) & 1);
	bouncer[OFFBUTR] = bouncer[OFFBUTR] << 1 | ((PINF >> 5) & 1);
	
	for (int i = 0; i < 6; i++) {
		if ((bouncer[i] & 0x3F) == 0x3F) buttonState |= (1 << i);
	}
}