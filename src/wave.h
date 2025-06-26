/*4:*/
#line 155 "weaver-interface-wave_en.cweb"

#ifndef __WEAVER_INTERFACE_WAVE
#define __WEAVER_INTERFACE_WAVE
#ifdef __cplusplus
extern"C"{
#endif
#line 161 "weaver-interface-wave_en.cweb"
#include <stdbool.h>  
#include <stdlib.h> 
/*1:*/
#line 65 "weaver-interface-wave_en.cweb"

void _extract_wave(void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void(*before_loading_interface)(void),
void(*after_loading_interface)(void),
char*source_filename,void*interface);
/*:1*/
#line 163 "weaver-interface-wave_en.cweb"

#ifdef __cplusplus
}
#endif
#line 167 "weaver-interface-wave_en.cweb"
#endif
#line 168 "weaver-interface-wave_en.cweb"
/*:4*/
