CXX=g++
CXXFLAGS=-Wall -std=c++1z
LDFLAGS=-ljack
SOURCE= main.o WaveTable.o Oscillator.o Sine.o Square.o Saw.o Synth.o KickSynth.o DetunedSaw.o Envelope.o writeToFile.o
TARGET=output

$(TARGET): $(SOURCE)
	$(CXX) -o $@ $(SOURCE) $(LDFLAGS)

plot:
	python3 plot.py output.csv

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $<
clean:
	rm -f $(TARGET) *.o *.csv
