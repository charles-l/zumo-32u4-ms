#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include "microscheme_types.c"

void init() {
  DDRB |= _BV(DDB6); // OUTPUT - left motor PWM
  DDRB |= _BV(DDB2); // OUTPUT - left motor direction

  DDRB |= _BV(DDB5); // OUTPUT - right motor PWM
  DDRB |= _BV(DDB1); // OUTPUT - right motor direction

  DDRD |= _BV(DDD3); // pin 1 - LCD control line
  PORTD &= ~(_BV(PORTD3)); // LO lcd

  // Timer 1 configuration
  // prescaler: clockI/O / 1
  // outputs enabled
  // phase-correct PWM
  // top of 400
  //
  // PWM frequency calculation
  // 16MHz / 1 (prescaler) / 2 (phase-correct) / 400 (top) = 20kHz
  TCCR1A = 0b10100000;
  TCCR1B = 0b00010001;
  ICR1 = 400;
  OCR1A = 0;
  OCR1B = 0;
}

static inline unsigned int clamp_speed(unsigned int speed) {
  if (speed > 400)  // Max
    return 400;
  return speed;
}

void set_left_speed(ms_value speed, ms_value rev) {
  speed = clamp_speed(speed);

  OCR1B = speed;

  if (asBool(rev)) {
    PORTB &= ~(_BV(PORTB2)); // set LO - forwards
  } else {
    PORTB |= _BV(PORTB2); // set HI - backewards
  }
}

void set_right_speed(ms_value speed, ms_value rev) {
  speed = clamp_speed(speed);

  OCR1A = speed;

  if (asBool(rev)) {
    PORTB &= ~(_BV(PORTB1)); // set LO - forwards
  } else {
    PORTB |= _BV(PORTB1); // set HI - backwards
  }
}
