ifeq ($(mode), debug)
    # Отладочная сборка: добавим генерацию отладочной информации
    CFLAGS += -g3
endif

ifeq ($(mode), release)
    # Финальная сборка: исключим отладочную информацию и утверждения (asserts)
    CFLAGS += -DNDEBUG -g0
endif

main.exe : text_func.o tree.o hash_func.o main.o
	gcc -o main.exe text_func.o tree.o hash_func.o main.o

text_func.o : text_func.c text_func.h
	gcc -std=c99 -c text_func.c

tree.o : tree.c tree.h
	gcc -std=c99 -c tree.c

hash_func.o : hash_func.c hash_func.h
	gcc -std=c99 -c hash_func.c

main.o : main.c text_func.h tree.h hash_func.h
	gcc -std=c99 -c main.c

clean : 
	rm *.o*.exe
