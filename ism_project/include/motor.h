#ifndef MOTOR
#define MOTOR

typedef struct cfg_moteur {
		uint16_t BI1;
		uint16_t BI2;
		uint16_t PWM;
	} cfg_moteur;

bool controler_moteur(cfg_moteur M, int16_t tension);

#endif 