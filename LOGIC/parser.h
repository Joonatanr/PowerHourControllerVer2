/*
 * parser.h
 *
 *  Created on: Aug 21, 2017
 *      Author: Joonatan
 */

#ifndef LOGIC_PARSER_H_
#define LOGIC_PARSER_H_

#include "typedefs.h"

Public char * parseU32FromString(U32 * dest, char * src);
Public Boolean parseCommaSeparatedU32Array(U32 * dest, char * src, U32 dest_len);
Public Boolean parseRectangle(char * src, Rectangle * dest);

#endif /* LOGIC_PARSER_H_ */
