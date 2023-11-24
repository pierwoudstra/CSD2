
output: Main.o Instrument.o StringedInstrument.o
	g++ Main.o Instrument.o StringedInstrument.o -o output

Main.o: Main.cpp
	g++ -c Main.cpp

Instrument.o: Instrument.cpp Instrument.h
	g++ -c Instrument.cpp

StringedInstrument.o: StringedInstrument.cpp StringedInstrument.h
	g++ -c StringedInstrument.cpp

clean:
	rm *.o output