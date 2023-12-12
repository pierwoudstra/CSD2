CXX=g++
CXXFLAGS=-Wall -std=c++1z
LDFLAGS=-ljack
SOURCE= main.o Synthesizer.o WaveTable.o Oscillator.o Envelope.o writeToFile.o
TARGET=output

$(TARGET): $(SOURCE)
	$(CXX) -o $@ $(SOURCE) $(LDFLAGS)

plot:
	./output
	python3 plot.py output.csv

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $<
clean:
	rm -f $(TARGET) *.o *.csv
