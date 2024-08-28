SHELL = cmd.exe

build:
	-mkdir build
	gcc -o build/main main.c isa/r_type/*.c ibex/*.c stages/*.c -Iisa -Iibex -Istages -Iisa/r_type -Wall -Wextra -Wpedantic -Wconversion -Wunused-variable -g -O0

clean:
	-rmdir /s /q build

run:
	.\build\main