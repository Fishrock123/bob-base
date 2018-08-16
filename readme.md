# BOB Status

C++ base class & status codes enum for the [BOB](https://github.com/Fishrock123/bob) streaming protocol.

In your `binding.gyp`:

```
  "include_dirs": [
    "<!(node -e \"require('bob-base')\")"
  ]
```

## Usage

### Base class

All C++ BOB interfaces *must* inherit from `BOB::Base` and implement its virtual functions:

```cpp
class My_Sink : public Bob_Base {
 public:
  My_Sink(<options>);
  virtual ~My_Sink();

  virtual Bob_Base* BindSource(Bob_Base* source);
  virtual void BindSink(Bob_Base* sink);
  virtual void Next(int status, void** error, char* data, size_t bytes);
  virtual void Pull(void** error, char* data, size_t size);

 private:
  Bob_Base* source_;
};
```

Sinks should implement `BindSource` roughly as so:

```cpp
Bob_Base* My_Sink::BindSource(Bob_Base* source) {
  source->BindSink(static_cast<Bob_Base*>(this));
  source_ = source;

  return this;
}
```

Sources should implement `BindSink` roughly as so:

```cpp
void FS_Source::BindSink(Bob_Base* sink) {
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
