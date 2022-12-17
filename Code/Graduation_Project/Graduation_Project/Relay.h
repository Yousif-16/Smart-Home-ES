/*
 * Relay.h
 *
 * Created: 9/8/2022 3:12:22 PM
 *  Author: Dell
 */ 


#ifndef RELAY_H_
#define RELAY_H_
#include "Relay_Configuration.h"

// Relay Functions
void Relay_Init(void);
void Relay_ON(void);
void Relay_OFF(void);
void Relay_Toggle(void);

#endif /* RELAY_H_ */