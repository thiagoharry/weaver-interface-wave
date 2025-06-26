/*5:*/
#line 190 "weaver-interface-wave_en.cweb"

#include "wave.h"
#include <AL/al.h> 
#include <AL/alc.h> 
#include <stdlib.h> 
#include <stdio.h> 
/*2:*/
#line 81 "weaver-interface-wave_en.cweb"

#include "interface.h"
/*:2*/
#line 196 "weaver-interface-wave_en.cweb"

/*3:*/
#line 128 "weaver-interface-wave_en.cweb"

static void*(*permanent_alloc)(size_t)= malloc;
static void*(*temporary_alloc)(size_t)= malloc;
static void(*permanent_free)(void*)= free;
static void(*temporary_free)(void*)= free;
/*:3*//*10:*/
#line 336 "weaver-interface-wave_en.cweb"

struct audio_data{
/*15:*/
#line 448 "weaver-interface-wave_en.cweb"

uint32_t channel;
uint64_t sample_rate;
/*:15*/
#line 338 "weaver-interface-wave_en.cweb"

};
/*:10*/
#line 197 "weaver-interface-wave_en.cweb"

/*11:*/
#line 353 "weaver-interface-wave_en.cweb"

bool read_chunk(FILE*fp,char*filename,struct audio_data*);
/*:11*//*13:*/
#line 389 "weaver-interface-wave_en.cweb"

bool read_unknown_chunk(FILE*fp,char*filename,struct audio_data*);
/*:13*//*16:*/
#line 456 "weaver-interface-wave_en.cweb"

bool read_fmt_chunk(FILE*fp,char*filename,struct audio_data*);
/*:16*/
#line 198 "weaver-interface-wave_en.cweb"

/*7:*/
#line 258 "weaver-interface-wave_en.cweb"

bool interpret_wave(char*filename,ALuint buffer){
FILE*fp;
fp= fopen(filename,"r");
if(fp==NULL){
perror(filename);
return false;
}
{
char buf[4];
size_t ret;

ret= fread(buf,1,4,fp);
if(ret!=4){
perror(filename);
return false;
}
if(buf[0]!='R'||buf[1]!='I'||buf[2]!='F'||buf[3]!='F'){
fprintf(stderr,"ERROR: %s not a RIFF file.\n",filename);
return false;
}

ret= fread(buf,1,4,fp);
if(ret!=4){
perror(filename);
return false;
}
/*8:*/
#line 306 "weaver-interface-wave_en.cweb"


ret= fread(buf,1,4,fp);
if(ret!=4){
perror(filename);
return false;
}
if(buf[0]!='W'||buf[1]!='A'||buf[2]!='V'||buf[3]!='E'){
fprintf(stderr,"ERROR: %s not a WAVE file.\n",filename);
return false;
}
/*:8*//*9:*/
#line 321 "weaver-interface-wave_en.cweb"

struct audio_data audio;
while(read_chunk(fp,filename,&audio));
/*:9*/
#line 285 "weaver-interface-wave_en.cweb"

}
fclose(fp);
return true;
}
/*:7*//*12:*/
#line 357 "weaver-interface-wave_en.cweb"

bool read_chunk(FILE*fp,char*filename,struct audio_data*audio){
size_t ret;

char type[4];
ret= fread(type,1,4,fp);
if(ret!=4){
if(feof(fp))
return false;
else{
perror(filename);
return false;
}
}
if(type[0]=='f'&&type[1]=='m'&&type[2]=='t'&&type[3]==' ')
return read_fmt_chunk(fp,filename,audio);
else if(type[0]=='d'&&type[1]=='a'&&type[2]=='t'&&type[3]=='a')
return read_data_chunk(fp,filename,audio);
else
return read_unknown_chunk(fp,filename,audio);
}
/*:12*//*14:*/
#line 393 "weaver-interface-wave_en.cweb"

bool read_unknown_chunk(FILE*fp,char*filename,struct audio_data*audio){
unsigned long size;
char buffer[4];
size_t ret;
ret= fread(buffer,1,4,fp);
if(ret!=4){
perror(filename);
return false;
}
size= buffer[0]+(256*buffer[1])+(256*256*buffer[2])+
(256*256*256*buffer[3]);
if(fseek(fp,size,SEEK_CUR)!=0){
perror(filename);
return false;
}
return true;
}
/*:14*//*17:*/
#line 460 "weaver-interface-wave_en.cweb"

bool read_fmt_chunk(FILE*fp,char*filename,struct audio_data*audio){
char buffer[8];
size_t ret;

if(fseek(fp,4,SEEK_CUR)!=0){
perror(filename);
return false;
}

ret= fread(buffer,1,4,fp);
if(ret!=4){
perror(filename);
return false;
}
if(buffer[0]!=1||buffer[1]!=0||buffer[2]!=0||buffer[3]!=0){
fprintf(stderr,"ERROR: WAV file %s is not in Microsoft PCM format.\n",
filename);
return false;
}

ret= fread(buffer,1,4,fp);
if(ret!=4){
perror(filename);
return false;
}
audio->channel= buffer[0]+256*buffer[1]+256*256*buffer[2]+
256*256*256*buffer[3];

ret= fread(buffer,1,8,fp);
if(ret!=8){
perror(filename);
return false;
}
audio->sample_rate= buffer[0]+
buffer[1]*256+
buffer[2]*256*256+
buffer[3]*256*256*256+
buffer[4]*256*256*256*256+
buffer[5]*256*256*256*256*256+
buffer[6]*256*256*256*256*256*256+
buffer[7]*256*256*256*256*256*256*256;

if(fseek(fp,12,SEEK_CUR)!=0){
perror(filename);
return false;
}
return true;
}
/*:17*/
#line 199 "weaver-interface-wave_en.cweb"

/*6:*/
#line 214 "weaver-interface-wave_en.cweb"

void _extract_wave(void*(*perm_alloc)(size_t),
void(*perm_free)(void*),
void*(*temp_alloc)(size_t),
void(*temp_free)(void*),
void(*before_loading_interface)(void),
void(*after_loading_interface)(void),
char*source_filename,void*interface){
struct sound*snd;
if(before_loading_interface!=NULL)
before_loading_interface();
snd= (struct sound*)interface;
permanent_alloc= perm_alloc;
permanent_free= perm_free;
temporary_alloc= temp_alloc;
temporary_free= temp_free;
if(interpret_wave(source_filename,snd->buffer))
snd->_loaded_sound= true;
if(after_loading_interface!=NULL)
after_loading_interface();
}
/*:6*/
#line 200 "weaver-interface-wave_en.cweb"

/*:5*/
