ifeq ($(mode), debug)
    # Отладочная сборка: добавим генерацию отладочной информации
    CFLAGS += -g3
endif

ifeq ($(mode), release)
    # Финальная сборка: исключим отладочную информацию и утверждения (asserts)
    CFLAGS += -DNDEBUG -g0
endif

main.exe : array.o timegen.o list.o main.o
	gcc -o main.exe array.o timegen.o list.o main.o

array.o : array.c array.h
	gcc -std=c99 -c array.c

timegen.o : timegen.c timegen.h
	gcc -std=c99 -c timegen.c

list.o : list.c list.h
	gcc -std=c99 -c list.c

main.o : main.c array.h timegen.h list.h
	gcc -std=c99 -c main.c

clean : 
	rm *.o*.exe