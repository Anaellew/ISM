Les modules : 

MOTEUR : 
	typedef struct cfg_moteur {
		uint16_t BI1,
		uint16_t BI2,
		uint16_t PWM,
	} cfg_moteur;
	bool controler_moteur(cfg_moteur M, int16_t tension);
	
ENCODEUR : 
	int16_t mesurer_vitesse(cfg_moteur);
	
	
Les services : 

ASSERVISSEMENT : 
	bool asservir_moteur(cfg_moteur M, int16_t vitesse);
	
PROTOCOLE : 
	bool invite_commande(uint16_t portSerie, ?? table_commande);
