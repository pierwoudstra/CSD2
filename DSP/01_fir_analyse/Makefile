CXX=g++
CXXFLAGS=-Wall -std=c++1z
SOURCE= main.o writeToFile.o
TARGET=output

$(TARGET): $(SOURCE)
	$(CXX) -o $@ $(SOURCE) $(LDFLAGS)

plot:
	python3 plot.py output.csv

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $<
clean:
	rm -f $(TARGET) *.o *.csv
