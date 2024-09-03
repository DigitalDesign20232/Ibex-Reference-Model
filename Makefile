SHELL = cmd.exe

build:
	-mkdir build
	gcc -o build/main main.c isa/r_type/*.c isa/i_type/*.c isa/s_type/*.c isa/b_type/*.c ibex/*.c stages/*.c memory/*.c utils/*.c -Iisa -Iibex -Istages -Iisa/r_type -Iisa/i_type -Iisa/s_type -Iisa/b_type -Imemory -Iutils -Wall -Wextra -Wpedantic -Wconversion -Wunused-variable -g -O0

clean:
	-rmdir /s /q build

run:
	.\build\main