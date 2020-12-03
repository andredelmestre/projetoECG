TARGET = prog

$(TARGET): main.o lib.a
	gcc $^ -o $@

main.o: main.c
	gcc -c $< -o $@

lib.a: andre.o
	ar rcs $@ $^

andre.o: andre.c andre.h
	gcc -c -o $@ $<

clean:
	rm -f *.o *.a $(TARGET)