// define max number of tasks to save precious Arduino RAM
#define TASKER_MAX_TASKS 6
#include "Tasker.h"



#define cidlo_otres 0        
#define sirenka 1      
#define led 2

unsigned int blikaniCas = 250;		//cas je v ms
unsigned int houkaniCas = 110;

long int vyhodnoceniCidlaCas;  // promena pro vyhodnocovani cidla
long int stavCidlaCas = 100;

int cidlo = 1;
boolean blikBezi = false;
boolean houkaniBezi = false;
boolean alarmBezi = false;
int predchoziStav = -1;           //ulozeni predchoziho stavu cidla




Tasker tasker (false);




void blikani (int pin) {
	if ( !blikBezi )return;						//povoleni/zakazani fuknce
	digitalWrite (pin, !digitalRead (pin));
	}

void houkaniStavPinu (int pin) {
	if ( !houkaniBezi ) return;
	//digitalWrite (pin, !digitalRead (pin));
	tone (pin, 4500, 50);
	noTone (2);
	tone (pin, 3500, 50);
	noTone (2);

	}
/*
void houkani (int pin) {
	if ( !houkaniBezi ) return;					//povoleni/zakazani fuknce
	tasker.setInterval (houkaniStavPinu, 430, pin);		// 6=3xpisk 200ms	
	}
*/
void alarmCasovani (int) {
	alarmBezi = true;

	tasker.setTimeout (stavCidla, stavCidlaCas);
	stavCidlaCas = stavCidlaCas + 1000;


	}


void stavCidla (int) {
	cidlo = digitalRead (cidlo_otres);

	}


void vyhodnoceniCidla (int) {             //zavolame v setup jako set.Interval
	
	if ( cidlo != predchoziStav ) {
		predchoziStav = cidlo;    //ulozeni aktualniho stavu cidla do historie
	

		if ( cidlo == 1 ) {

			blikBezi = true;                //povoleni blikani
			houkaniBezi = true;				//povolime houkani
			
			
			}
		else {

			blikBezi = false;               //vypneme blikani
			houkaniBezi = false;			//vypneme houkani	
			digitalWrite (led, LOW);
			}
		}

	}


void setup ( ) {
	pinMode (cidlo_otres, INPUT);  
	pinMode (sirenka, OUTPUT); 
	pinMode (led, OUTPUT); 
	

	tasker.setInterval (stavCidla, 1);
	tasker.setInterval (vyhodnoceniCidla, 50);
	tasker.setInterval (blikani, blikaniCas, led);
	tasker.setInterval (houkaniStavPinu, houkaniCas, sirenka);


	tasker.run ( );
	}

void loop ( ) {
	}