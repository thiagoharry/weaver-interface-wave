/*5:*/
#line 189 "weaver-interface-wave_en.cweb"

#include "wave.h"
/*2:*/
#line 81 "weaver-interface-wave_en.cweb"

#include "interface.h"
/*:2*/
#line 191 "weaver-interface-wave_en.cweb"

/*3:*/
#line 128 "weaver-interface-wave_en.cweb"

static void*(*permanent_alloc)(size_t)= malloc;
static void*(*temporary_alloc)(size_t)= malloc;
static void(*permanent_free)(void*)= free;
static void(*temporary_free)(void*)= free;
/*:3*/
#line 192 "weaver-interface-wave_en.cweb"



/*:5*/
