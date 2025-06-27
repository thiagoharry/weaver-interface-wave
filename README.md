# weaver-interface-wave

This project is part of the [Weaver Game
Engine](https://github.com/thiagoharry/weaver). It adds support for
WAVE audio files to the engine.

This is written using Literate Programming. If you want to study how the
library works, you can read the full source code with explanatory text
in
[weaver-interface-wave_en.pdf](https://github.com/thiagoharry/weaver-interface-wave/blob/master/weaver-interface-wave_en.pdf)
(engish version) or
[weaver-interface-wave.pdf](https://github.com/thiagoharry/weaver-interface-wave/blob/master/weaver-interface-wave.pdf)
(portuguese version).

This submodule exports a single function:

```
  void _extract_wave(void *(*permanent_alloc)(size_t),
                     void (*permanent_free)(void *),
                     void *(*temporary_alloc)(size_t),
                     void (*temporary_free)(void *),
                     void (*before_loading_interface)(void),
                     void (*after_loading_interface)(void),
                     char *source_filename, void *interface);
```

The function extracts audio data from a source file, assuming it is in
WAVE format. The function is compatible with the [Weaver Interface
submodule](https://github.com/thiagoharry/weaver-interface).