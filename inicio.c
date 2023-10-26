/*
 * main.c
 *
 * Created: 10/24/2023 4:26:37 PM
 *  Author: rodrigo
 */ 
#define F_CPU 1000000UL
#include <stdio.h>
#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>



void esperar_inicio(uint8_t inicio);

void adelante(); //avanza a toda la velocidad posible
void atras(); //retrocede a un 100% de su velocidad

int main(void){
    uint8_t inicio=0;
	DDRD=0xff;
	DDRB=0x01;
	PORTB=0x00;
	esperar_inicio(inicio); // Espera a que el pulsador se presione para empezar la rutina 
	
	while(1){
	_delay_ms(10000);
    while(inicio!=0x02)//si el boton se vuelve a presionar la rutina se realiza por ultima vez y luego espera quieto
    {			
		inicio=PINB & 0x02;
      
	 adelante();
	 
	  _delay_ms(50000); //espera 5 segundos
	 
	  atras();
	  
	  _delay_ms(50000); // espera 5 segundos
		  
	  } 
	  PORTD=0x00;
	  _delay_ms(10000);
	 esperar_inicio(inicio); 
	}
	return 0;
}

void esperar_inicio(uint8_t inicio)	{
inicio=PINB & 0x02;
if(inicio!=0){
}
else{
esperar_inicio(inicio);
}	
	}

void adelante()	{
 PORTD &= ~(1 << PORTD3);
 PORTD &= ~(1 << PORTD4);
 
 PORTD |= (1 << PORTD2);
 PORTD |= (1 << PORTD5);
}
	
void atras()	{
	PORTD &= ~(1 << PORTD2);

	PORTD |= (1 << PORTD3);

	// PORTD &= ~(1 << PORTD5);
	
	PORTD |= (1 << PORTD4);
	PORTD &= ~(1 << PORTD5);

	
}