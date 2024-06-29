CC := gcc

build/%.o: src/%.c
	mkdir -p build
	${CC} ${NIX_CFLAGS_COMPILE} -Wfatal-errors $< -o $@ -c

main: build/main.o build/kissinger2.o
	${CC} ${NIX_CFLAGS_COMPILE} -lSDL2 $^ -o $@

src/kissinger2.c: generate_kissinger2_c.py build/kissinger2dev4.zip
	python generate_kissinger2_c.py gencode

build/kissinger2dev4.zip:
	mkdir -p build
	curl https://typedesign.replit.app/kissinger2dev4.zip -o $@
