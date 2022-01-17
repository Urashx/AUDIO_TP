/*
 * audio_processing.h
 *
 *  Created on: May 17, 2021
 *      Author: sydxrey
 */

#ifndef INC_AUDIO_H_
#define INC_AUDIO_H_

#include "stdint.h"
#include <main.h>

void audioLoop(osThreadId * audio, osThreadId * ui) ;
void uiLoop();

#endif /* INC_AUDIO_H_ */
