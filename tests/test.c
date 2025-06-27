#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#if defined(_WIN32)
#include <Windows.h>
#else
#include <sys/time.h>
#endif

#include <AL/al.h>
#include <AL/alc.h>

#if defined(__EMSCRIPTEN__)
#include <emscripten.h>
#endif

#include "../src/interface.h"
#include "../src/wave.h"

#include <AL/al.h>
#include <AL/alc.h>

ALCdevice *device;
ALCcontext *context;
ALuint source;

int numero_de_testes = 0, acertos = 0, falhas = 0;
void imprime_resultado(void){
  printf("\n%d tests: %d sucess, %d fails\n\n",
	 numero_de_testes, acertos, falhas);
}

void assert(char *descricao, bool valor){
  char pontos[72], *s = descricao;
  size_t tamanho_string = 0;
  int i;
  while(*s)
    tamanho_string += (*s++ & 0xC0) != 0x80;
  pontos[0] = ' ';
  for(i = 1; i < 71 - (int) tamanho_string; i ++)
    pontos[i] = '.';
  pontos[i] = '\0';
  numero_de_testes ++;
  printf("%s%s", descricao, pontos);
  if(valor){
#if defined(__unix__) && !defined(__EMSCRIPTEN__)
    printf("\e[32m[OK]\033[0m\n");
#else
    printf("[OK]\n");
#endif
    acertos ++;
  }
  else{
#if defined(__unix__) && !defined(__EMSCRIPTEN__)
    printf("\033[0;31m[FAIL]\033[0m\n");
#else
    printf("[FAIL]\n");
#endif
    falhas ++;
  }
}

void test_audio_mouseclick(void){
  struct sound s;
  int source_state;
  _extract_wave(malloc, free, malloc, free, NULL, NULL,
		"tests/samples/mouseclick.wav", &s);
  alSourcei(source, AL_BUFFER, s.buffer);
  alSourcePlay(source);
  alGetSourcei(source, AL_SOURCE_STATE, &source_state);
  while (source_state == AL_PLAYING) {
    alGetSourcei(source, AL_SOURCE_STATE, &source_state);
  }
  assert("Interpreting file mouseclick.wav", s._loaded_sound &&
	 s.buffer != 0 && alGetError() == AL_NO_ERROR);
}

int main(int argc, char **argv){
  device = alcOpenDevice(NULL);
  alGetError();
  context = alcCreateContext(device, NULL);
  alcMakeContextCurrent(context);
  alGenSources((ALuint)1, &source);
  alSourcef(source, AL_PITCH, 1);
  alSourcef(source, AL_GAIN, 1);
  alSource3f(source, AL_POSITION, 0, 0, 0);
  alSource3f(source, AL_VELOCITY, 0, 0, 0);
  alSourcei(source, AL_LOOPING, AL_FALSE);
  test_audio_mouseclick();
  imprime_resultado();
  return 0;
}
