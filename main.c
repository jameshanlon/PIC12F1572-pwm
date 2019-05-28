/*
 * PIC12F1572 PWM example.
 *
 * Pins:
 *                     +----+
 *                Vdd -|1  8|- Vss
 *           PWM1 RA5 -|2  7|- RA0/ICSPDAT
 *           PWM2 RA4 -|3  6|- RA1/ICSPLCK
 *           RA3/MCLR -|4  5|- RA2 PWM3
 *                     +----+
 */

#include <xc.h>

#define _XTAL_FREQ 16000000   // Oscillator frequency.

#pragma config FOSC = INTOSC  // INTOSC oscillator: I/O function on CLKIN pin.
#pragma config WDTE = OFF     // Watchdog Timer disable.
#pragma config PWRTE = OFF    // Power-up Timer enbable.
#pragma config MCLRE = ON     // MCLR/VPP pin function is MCLR.
#pragma config CP = OFF       // Program memory code protection disabled.
#pragma config BOREN = ON     // Brown-out Reset enabled.
#pragma config CLKOUTEN = OFF // CLKOUT function is disabled; I/O or oscillator function on the CLKOUT pin.
#pragma config WRT = OFF      // Flash Memory Write protection off.
#pragma config STVREN = ON    // Stack Overflow or Underflow will cause a Reset.
#pragma config BORV = LO      // Brown-out Reset Voltage (Vbor), low trip point selected.
#pragma config LVP = OFF      // High-voltage on MCLR/VPP must be used for programming.

#include <stdio.h>
#include <stdlib.h>

void init_pic() {
  OSCCON = 0b01111010; // 16 Mhz oscillator.
  ANSELA = 0;          // Analog off.
  LATA = 0;            // Zero all port bits.
}

void init_pwm() {
  // Pin selection.
  APFCONbits.P1SEL = 1; // PWM1 on RA5.
  APFCONbits.P2SEL = 1; // PWM2 on RA4.

  // Set PWM pins to be outputs.
  TRISAbits.TRISA2 = 0;
  TRISAbits.TRISA4 = 0;
  TRISAbits.TRISA5 = 0;

  // Set HFINTOSC clock, no prescaler.
  PWM1CLKCON = 0b00000001;
  PWM2CLKCON = 0b00000001;
  PWM3CLKCON = 0b00000001;

  // PWM control (standard mode).
  PWM1CON = 0b11000000;
  PWM2CON = 0b11000000;
  PWM3CON = 0b11000000;

  // Phase.
  PWM1PH = 0;
  PWM2PH = 0;
  PWM3PH = 0;

  // Duty cycle.
  PWM1DC = 0;
  PWM2DC = 0;
  PWM3DC = 0;

  // Period.
  PWM1PR = 32768;
  PWM2PR = 32768;
  PWM3PR = 32768;
}

int main() {
  init_pic();
  init_pwm();
  while (1)  {
    PWM1DC += 10;
    PWM1LD = 1;
    PWM2DC += 10;
    PWM2LD = 1;
    PWM3DC += 10;
    PWM3LD = 1;
    __delay_ms(10);
  }
  return (EXIT_SUCCESS);
}
