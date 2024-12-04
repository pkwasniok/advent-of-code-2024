CFLAGS = -std=c23
CFLAGS += -Werror

run: build
	./.build/main

build: main.c
	gcc $(CFLAGS) main.c -o .build/main

