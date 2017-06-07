start: multithreaded_cons_vowel.o
	clang++ -std=c++11 -stdlib=libc++ multithreaded_cons_vowel.o -o start

multithreaded_cons_vowel.o: multithreaded_cons_vowel.cpp
	clang++ -std=c++11 -stdlib=libc++ -c multithreaded_cons_vowel.cpp
    
clean:
	rm *.o start