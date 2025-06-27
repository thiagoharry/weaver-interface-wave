/*4:*/
#line 170 "weaver-interface-wave.cweb"

#ifndef __WEAVER_INTERFACE_WAVE
#define __WEAVER_INTERFACE_WAVE
#ifdef __cplusplus
extern"C"{
#endif
#line 176 "weaver-interface-wave.cweb"
#include <stdbool.h>  
#include <stdlib.h> 
/*1:*/
#line 75 "weaver-interface-wave.cweb"

void _extract_wave(void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void(*before_loading_interface)(void),
void(*after_loading_interface)(void),
char*source_filename,void*interface);
/*:1*/
#line 178 "weaver-interface-wave.cweb"

#ifdef __cplusplus
}
#endif
#line 182 "weaver-interface-wave.cweb"
#endif
#line 183 "weaver-interface-wave.cweb"
/*:4*/
