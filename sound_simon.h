/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   sound_simon.h
 * Author: matias
 *
 * Created on 2 de diciembre de 2016, 11:06
 */

#ifndef SOUND_SIMON_H
#define SOUND_SIMON_H

void inicializar_sonido(void);
void set_audio_vars(void);
void * play_sound_button(void * v);
void sound_mute (void);
void sound_unmute(void);
void perdi(void);
void stop_thread_sound(void);
#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* SOUND_SIMON_H */

