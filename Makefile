all: makeProje run

makeProje: main.o Proje1.o
	gcc main.o Proje1.o -o makeProje

main.o: main.c Proje1.h
	gcc -c main.c

Proje1.o: Proje1.c Proje1.h
	gcc -c Proje1.c

clean:
	rm -f *.o makeProje

run:
	./makeProje Birimler.txt Calisanlar.txt
