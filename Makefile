doc:
	magitex-cweb weaver-interface-wave.cweb
	dvipdf weaver-interface-wave.dvi
doc_en:
	tex weaver-interface-wave_en.cweb
	dvipdf weaver-interface-wave_en.dvi
test:
	ctangle weaver-interface-wave.cweb
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -DW_FORCE_LANDSCAPE -DW_DEBUG_INTERFACE -Wall -O2 tests/test.c src/interface.c src/wave.c -o test_interface -lX11 -lEGL -lGLESv2 -lm -lopenal
	./test_interface
test_en:
	ctangle weaver-interface-wave_en.cweb
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -DW_FORCE_LANDSCAPE -DW_DEBUG_INTERFACE -Wall -O2 tests/test.c  src/interface.c src/wave.c -o test_interface -lX11 -lEGL -lGLESv2 -lm -lopenal
	./test_interface
test_web:
	ctangle weaver-interface.cweb
	emcc $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -DW_FORCE_LANDSCAPE -s ASYNCIFY=1 -Wall -O2 tests/test.c tests/window.c src/interface.c  -o docs/test_interface.html
test_web_en:
	ctangle weaver-window_en.cweb
	emcc $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -DW_FORCE_LANDSCAPE -s ASYNCIFY=1 -Wall -O2 tests/test.c tests/window.c src/interface.c  -o docs/test_interface.html
clean:
	rm -f *~ *.core *.scn *.dvi *.idx *.log 
