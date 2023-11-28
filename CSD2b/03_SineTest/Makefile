CXX=g++
CXXFLAGS=-Wall -std=c++1z
LDFLAGS=
SOURCE= writeToFile.o Sine.o Oscillator.o main.o
TARGET=output

$(TARGET): $(SOURCE)
	$(CXX) -o $@ $(SOURCE) $(LDFLAGS)
	rm *.o

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $<
clean:
	rm -f $(TARGET) *.o *.csv
