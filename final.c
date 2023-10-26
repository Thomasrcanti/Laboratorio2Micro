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
void adelante80(); //avanza a un 80% de su velocidad
void adelante60(); //avanza a un 60% de su velocidad
void adelante40(); //avanza a un 40% de su velocidad
void atras(); //retrocede a un 100% de su velocidad
void derecha(); //gira a la derecha 
void izquierda(); //gira a la izquierda


void ADC_init() {
	// Configurar referencia de voltaje a AVCC con capacitor de desacoplo
	ADMUX |= (1 << REFS0);
	// Habilitar el ADC y configurar el prescaler a 128 para un rango de 0-5V
	ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t ADC_read(uint8_t channel) {
	// Seleccionar el canal de entrada
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
	
	// Iniciar la conversion
	ADCSRA |= (1 << ADSC);
	
	// Esperar a que la conversion se complete
	while (ADCSRA & (1 << ADSC));
	
	return ADC;
}



int main(void){
    uint8_t inicio=0;
	DDRD=0xff;
	DDRB=0x01;
	PORTB=0x00;
	esperar_inicio(inicio); // Espera a que el pulsador se presione para empezar la rutina 
	
	// Inicializar el ADC
	ADC_init();

	uint16_t adc_value;

	// Configurar el pin de salida para indicar el estado del potenciometro
	DDRB |= (1 << PORTB0);

	
	while(1){
	_delay_ms(10000);
    while(inicio!=0x02)//si el boton se vuelve a presionar la rutina se realiza por ultima vez y luego espera quieto
    {
		// Leer el valor ADC desde el potenciometro
		adc_value = ADC_read(0);

		if (adc_value > 700) {
			PORTB |= (1 << PORTB0);
		}
		else {
			PORTB &= ~(1 << PORTB0);
		}
		
		
		inicio=PINB & 0x02;
      
	 adelante();
	 
	  _delay_ms(50000); //espera 5 segundos
	
	  adelante80();
	 	 
	  adelante60();
	  	
      adelante40();
	 
	  atras();
	  
	  _delay_ms(50000); // espera 5 segundos
	 
	  derecha();
		 
	  izquierda();
		  
	  } 
	  PORTD=0x00;
	  _delay_ms(10000);
	 esperar_inicio(inicio); 
	}
	return 0;
}

void esperar_inicio(uint8_t inicio){
inicio=PINB & 0x02;
if(inicio!=0){
}
else{
esperar_inicio(inicio);
}}

void adelante(){
 PORTD &= ~(1 << PORTD3);
 PORTD &= ~(1 << PORTD4);
 
 PORTD |= (1 << PORTD2);
 PORTD |= (1 << PORTD5);
}

void adelante80(){
	for(int i=0;i<10000;i++){
	PORTD &= ~(1 << PORTD3);
	PORTD &= ~(1 << PORTD4);
	PORTD &= ~(1 << PORTD2);
	PORTD &= ~(1 << PORTD5);
	 _delay_ms(1);
	PORTD |= (1 << PORTD2);
	PORTD |= (1 << PORTD5);
	_delay_ms(4);
	}
}

void adelante60(){
	for(int i=0;i<10000;i++){
	PORTD &= ~(1 << PORTD3);
	PORTD &= ~(1 << PORTD4);
	PORTD &= ~(1 << PORTD2);
	PORTD &= ~(1 << PORTD5);
	_delay_ms(3);
	PORTD |= (1 << PORTD2);
	PORTD |= (1 << PORTD5);
	_delay_ms(2);
	}
}

void adelante40(){
	for(int i=0;i<10000;i++){
	PORTD &= ~(1 << PORTD3);
	PORTD &= ~(1 << PORTD4);
	PORTD &= ~(1 << PORTD2);
	PORTD &= ~(1 << PORTD5);
	_delay_ms(3);
	PORTD |= (1 << PORTD2);
	PORTD |= (1 << PORTD5);
	_delay_ms(2);
	}
}

void atras(){
	PORTD &= ~(1 << PORTD2);

	PORTD |= (1 << PORTD3);

	// PORTD &= ~(1 << PORTD5);
	
	PORTD |= (1 << PORTD4);
	PORTD &= ~(1 << PORTD5);

	
}

void derecha(){
	for(int i=0;i<5000;i++){
	PORTD &= ~(1 << PORTD3);

	PORTD |= (1 << PORTD2);
	
	PORTD |= (1 << PORTD5);
	_delay_ms(3);
	PORTD &= ~(1 << PORTD5);
	PORTD &= ~(1 << PORTD4);
    _delay_ms(7);
	}
}

void izquierda(){
	for(int i=0;i<5000;i++){
	PORTD &= ~(1 << PORTD2);
	PORTD &= ~(1 << PORTD3);
	_delay_ms(7);
	PORTD &= ~(1 << PORTD4);

	PORTD |= (1 << PORTD5);
	
	PORTD |= (1 << PORTD2);
	_delay_ms(3);}
}