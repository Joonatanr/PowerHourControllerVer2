/*
 * SnakeMain.h
 *
 *  Created on: 23. mai 2018
 *      Author: JRE
 */

#ifndef LOGIC_SNAKEGAME_SNAKEMAIN_H_
#define LOGIC_SNAKEGAME_SNAKEMAIN_H_

#include "typedefs.h"

extern void snake_init(void);
extern void snake_start(void);
extern void snake_cyclic100ms(void);
extern void snake_stop(void);

/* TODO : This should be made into a general implementation for returning to the main menu. */
extern void returnToMain(void);

#endif /* LOGIC_SNAKEGAME_SNAKEMAIN_H_ */
