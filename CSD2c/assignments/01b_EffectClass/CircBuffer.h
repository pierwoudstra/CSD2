#ifndef INC_01_CIRCULARBUFFER_CIRCBUFFER_H
#define INC_01_CIRCULARBUFFER_CIRCBUFFER_H

class CircBuffer {
public:
  CircBuffer(int size);
  ~CircBuffer();

  // write & increment write head & wrap
  void write(float input);
  // read & increment read head & wrap
  float read();

  void setReadHead(int readHead);

private:
  float* buffer;
  int readHead;
  int writeHead;
  int size;

  void wrapReadHead();
  void wrapWriteHead();
};

#endif // INC_01_CIRCULARBUFFER_CIRCBUFFER_H
