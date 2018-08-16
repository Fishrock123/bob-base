#ifndef BOB_H_
#define BOB_H_

namespace BOB {

enum Status {
  ERROR = -1,
  END = 0,
  CONTINUE = 1
};

class Base {
 public:
  virtual ~Base();

  virtual Base* BindSource(Base* source) = 0;
  virtual void BindSink(Base* sink) = 0;
  virtual void Next(int status, void** error, char* data, size_t bytes) = 0;
  virtual void Pull(void** error, char* data, size_t size) = 0;
};

} // namespace BOB

#endif  // BOB_H_
