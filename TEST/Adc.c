#include "Adc.h"

void initADC() 
{
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK; // setam bitul 27 pentru  a activa ADC0
	
	ADC0->CFG1 |= 	(ADC_CFG1_MODE(0) | ADC_CFG1_ADIV(3)); // setam in ADC Configuiration register 1 Bitii ce apartin pentru mode cu 0 si cei pentru adiv cu 1(amandoi) (rata de diviziune 8 si o singura conversiue pe 8 biti )
	
	ADC0_SC1A = ADC_SC1_ADCH(31); //dezactivare prin setarea tuturor bitilor ( 4 la numar )
	
}

uint8_t ADC_Read8b(uint16_t channel)
{
	ADC0_SC1A = channel & ADC_SC1_ADCH_MASK; //Activez monitorizarea pe canalul dorit (determinat de pinul de input)
	
	while(ADC0_SC2 & ADC_SC2_ADACT_MASK); //Verific daca o conversie este in desfasurare
	while(!(ADC0_SC1A & ADC_SC1_COCO_MASK)); //Verific daca conversia s-a realizat
	return ADC0_RA;  // returnam ce se afla in registrul ADC DATA RESTULT
	
}

void calibrateADC()
{
	ADC0_SC2 |= ADC_SC2_ADTRG(0);
	ADC0_SC3 |= (1<<6 );//setam bitul 7 pentru a incepe o calibrare automata daca SC2[ADTRG] este 0.
	uint16_t aux;
	aux = ADC0_CLP0; //ADC Plus-Side General Calibration Value Register
	aux+=ADC0_CLP1;
	aux+=ADC0_CLP2;
	aux+=ADC0_CLP3;
	aux+=ADC0_CLP4;
	aux+=ADC0_CLPS;
	aux /=2;
	aux |= aux &0x8000;
	ADC0_PG |= aux; //ADC Plus-Side General Calibration Value Register
	uint16_t auxMinus;
	auxMinus= ADC0_CLM0; //ADC Minus-Side General Calibration Value Register
	auxMinus+= ADC0_CLM1;
	auxMinus+= ADC0_CLM2;
	auxMinus+= ADC0_CLM3;
	auxMinus+= ADC0_CLM4;
	auxMinus+= ADC0_CLMD;
	auxMinus/=2;
	auxMinus|=auxMinus&0x8000;
	ADC0_MG=auxMinus;  //ADC Minus-Side General Calibration Value Register
	
}