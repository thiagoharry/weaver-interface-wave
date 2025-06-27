/*5:*/
#line 206 "weaver-interface-wave.cweb"

#include "wave.h"
#include <AL/al.h> 
#include <AL/alc.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
/*2:*/
#line 91 "weaver-interface-wave.cweb"

#include "interface.h"
/*:2*/
#line 213 "weaver-interface-wave.cweb"

/*3:*/
#line 140 "weaver-interface-wave.cweb"

static void*(*permanent_alloc)(size_t)= malloc;
static void*(*temporary_alloc)(size_t)= malloc;
static void(*permanent_free)(void*)= free;
static void(*temporary_free)(void*)= free;
/*:3*//*10:*/
#line 354 "weaver-interface-wave.cweb"

struct audio_data{
/*15:*/
#line 471 "weaver-interface-wave.cweb"

uint16_t channel,bits_per_sample;
uint32_t sample_rate;
/*:15*//*18:*/
#line 542 "weaver-interface-wave.cweb"

bool initialized;
size_t buffer_size;
unsigned char*buffer;
/*:18*/
#line 356 "weaver-interface-wave.cweb"

};
/*:10*/
#line 214 "weaver-interface-wave.cweb"

/*11:*/
#line 371 "weaver-interface-wave.cweb"

bool read_chunk(FILE*fp,char*filename,struct audio_data*);
/*:11*//*13:*/
#line 406 "weaver-interface-wave.cweb"

bool read_unknown_chunk(FILE*fp,char*filename);
/*:13*//*16:*/
#line 479 "weaver-interface-wave.cweb"

bool read_fmt_chunk(FILE*fp,char*filename,struct audio_data*);
/*:16*//*19:*/
#line 558 "weaver-interface-wave.cweb"

bool read_data_chunk(FILE*fp,char*filename,struct audio_data*);
/*:19*/
#line 215 "weaver-interface-wave.cweb"

/*7:*/
#line 278 "weaver-interface-wave.cweb"

bool interpret_wave(char*filename,ALuint buffer){
FILE*fp;
fp= fopen(filename,"r");
if(fp==NULL){
perror(filename);
return false;
}
{
unsigned char buf[4];
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
#line 323 "weaver-interface-wave.cweb"


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
#line 338 "weaver-interface-wave.cweb"

struct audio_data audio;
memset(&audio,0,sizeof(struct audio_data));
while(read_chunk(fp,filename,&audio));
/*:9*//*21:*/
#line 606 "weaver-interface-wave.cweb"

{
ALenum error,format= 0;
if(audio.channel==1){
if(audio.bits_per_sample==8)
format= AL_FORMAT_MONO8;
else if(audio.bits_per_sample==16)
format= AL_FORMAT_MONO16;
}
else if(audio.channel==2){
if(audio.bits_per_sample==8)
format= AL_FORMAT_STEREO8;
else if(audio.bits_per_sample==16)
format= AL_FORMAT_STEREO16;
}
else{
fprintf(stderr,"ERROR: %s has %d channels, but we support at most 2.\n",
filename,audio.channel);
return false;
}
if(audio.bits_per_sample!=8&&audio.bits_per_sample!=16){
fprintf(stderr,"ERROR: %s uses %d bits per sample, but we support "
"only 8 or 16.\n",filename,audio.bits_per_sample);
return false;
}
alBufferData(buffer,format,audio.buffer,audio.buffer_size,
audio.sample_rate);
error= alGetError();
if(error==AL_OUT_OF_MEMORY){
fprintf(stderr,"ERROR: OpenAL: No memory!\n");
return false;
}
else if(error!=AL_NO_ERROR){
fprintf(stderr,"ERROR: %s: OpenAL: Unexpected error.\n",filename);
return false;
}
if(temporary_free!=NULL)
temporary_free(audio.buffer);
return true;
}
/*:21*/
#line 305 "weaver-interface-wave.cweb"

}
fclose(fp);
return true;
}
/*:7*//*12:*/
#line 375 "weaver-interface-wave.cweb"

bool read_chunk(FILE*fp,char*filename,struct audio_data*audio){
size_t ret;

unsigned char type[4];
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
return read_unknown_chunk(fp,filename);
}
/*:12*//*14:*/
#line 410 "weaver-interface-wave.cweb"

bool read_unknown_chunk(FILE*fp,char*filename){
unsigned long size;
unsigned char buffer[4];
size_t ret;
ret= fread(buffer,1,4,fp);
if(ret!=4){
perror(filename);
return false;
}
size= buffer[0]+(256*buffer[1])+(256*256*buffer[2])+
(256*256*256*buffer[3]);
printf("size: %lu\n",size);
if(fseek(fp,size,SEEK_CUR)!=0){
perror(filename);
return false;
}
return true;
}
/*:14*//*17:*/
#line 483 "weaver-interface-wave.cweb"

bool read_fmt_chunk(FILE*fp,char*filename,struct audio_data*audio){
unsigned char buffer[4];
size_t ret;

if(fseek(fp,4,SEEK_CUR)!=0){
perror(filename);
return false;
}

ret= fread(buffer,1,2,fp);
if(ret!=2){
perror(filename);
return false;
}
if(buffer[0]!=1||buffer[1]!=0){
fprintf(stderr,"ERROR: WAV file %s is not in Microsoft PCM format.\n",
filename);
return false;
}

ret= fread(buffer,1,2,fp);
if(ret!=2){
perror(filename);
return false;
}
audio->channel= buffer[0]+256*buffer[1];

ret= fread(buffer,1,4,fp);
if(ret!=4){
perror(filename);
return false;
}
audio->sample_rate= buffer[0]+
buffer[1]*256+
buffer[2]*256*256+
buffer[3]*256*256*256;

if(fseek(fp,6,SEEK_CUR)!=0){
perror(filename);
return false;
}

ret= fread(buffer,1,2,fp);
if(ret!=2){
perror(filename);
return false;
}
audio->bits_per_sample= buffer[0]+256*buffer[1];
return true;
}
/*:17*//*20:*/
#line 562 "weaver-interface-wave.cweb"

bool read_data_chunk(FILE*fp,char*filename,struct audio_data*audio){
unsigned char buffer[4];
size_t size,ret;

ret= fread(buffer,1,4,fp);
if(ret!=4){
perror(filename);
return false;
}
size= buffer[0]+
buffer[1]*256+
buffer[2]*256*256+
buffer[3]*256*256*256;
if(audio->initialized){

if(fseek(fp,size,SEEK_CUR)!=0){
perror(filename);
return false;
}
return true;
}


audio->buffer= (unsigned char*)temporary_alloc(size);
if(audio->buffer==NULL){
fprintf(stderr,"ERROR: No memory to copy audio data from %s.\n",
filename);
return false;
}
audio->buffer_size= size;
ret= fread(audio->buffer,1,size,fp);
if(ret!=size){
perror(filename);
return false;
}
return true;
}
/*:20*/
#line 216 "weaver-interface-wave.cweb"

/*6:*/
#line 231 "weaver-interface-wave.cweb"

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
alGenBuffers(1,&(snd->buffer));
if(interpret_wave(source_filename,snd->buffer))
snd->_loaded_sound= true;
else{
alDeleteBuffers(1,&(snd->buffer));
snd->buffer= 0;
}
if(after_loading_interface!=NULL)
after_loading_interface();
}
/*:6*/
#line 217 "weaver-interface-wave.cweb"

/*:5*/
