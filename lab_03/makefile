ifeq ($(mode), debug)
    # Отладочная сборка: добавим генерацию отладочной информации
    CFLAGS += -g3
endif

ifeq ($(mode), release)
    # Финальная сборка: исключим отладочную информацию и утверждения (asserts)
    CFLAGS += -DNDEBUG -g0
endif

main.exe : array_stack.o main.o
	gcc -o main.exe array_stack.o main.o

array_stack.o : array_stack.c array_stack.h
	gcc -std=c99 -c array_stack.c
 
main.o : main.c array_stack.h
	gcc -std=c99 -c main.c

clean : 
	rm *.o*.exe
