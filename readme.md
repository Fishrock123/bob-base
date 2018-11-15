# BOB Base

C++ base class & status codes enum for the [BOB](https://github.com/Fishrock123/bob) streaming protocol.

In your `binding.gyp`:

```
  "include_dirs": [
    "<!(node -e \"require('bob-base')\")"
  ]
```

In your C++:

```cpp
#include <bob.h>
```

## Usage

### Base class

All C++ BOB interfaces *must* inherit from `BOB::Base` and implement its virtual functions:

```cpp
class My_Sink : public BOB::Base {
 public:
  My_Sink(<options>);
  virtual ~My_Sink();

  virtual BOB::Base* BindSource(BOB::Base* source);
  virtual void BindSink(BOB::Base* sink);
  virtual void Next(int status, void** error, char* data, size_t bytes);
  virtual void Pull(void** error, char* data, size_t size);

 private:
  BOB::Base* source_;
};
```

Sinks should implement `BindSource` roughly as so:

```cpp
BOB::Base* My_Sink::BindSource(BOB::Base* source) {
  source->BindSink(static_cast<BOB::Base*>(this));
  source_ = source;

  return this;
}
```

Sources should implement `BindSink` roughly as so:

```cpp
void FS_Source::BindSink(BOB::Base* sink) {
  sink_ = sink;
}
```

Functions specific to sources or sinks may exit the program if invoked:

```cpp
void My_Sink::Pull(void** error, char* data, size_t size) {
  printf("Sinks do not have a public ::Pull!");
  abort();
}
```

### Status enum

- Send `Status::CONTINUE` as the first argument to a BOB sink's `next()` method in most cases.
- Send `Status::END` as the first argument to a BOB sink's `next()` to end the stream.
- Send `Status::ERROR` as the first argument to a BOB sink's `next()` if there is an error.

## License

[MIT Licensed](license) — _[Contributions via DCO 1.1](contributing.md#developers-certificate-of-origin)_
