# scu

scu is a set of Single-header C Utilities inspired by
[nothings/stb](https://github.com/nothings/stb).

As such, as you may have guessed, each utility is a single header file. You can
use it as such or you may define `SCU_<name>_IMPLEMENTATION` to include the
implementation.

## Tests

This repo is using [check](https://libcheck.github.io/check/) as a testing
library. 

### Build

To build and run these tests I'm using
[nob](https://github.com/tsoding/musializer/blob/master/nob.c).
Which is a C only build tool created by [tsoding](https://github.com/tsoding/).

### Testing Quickstart

```console
$ cc -o ./nob nob.c
$ ./nob
```

This will build and run all the tests provided in the `./tests` directory.
If you where to edit `nob.c` it will rebuild itself when running `./nob`.
