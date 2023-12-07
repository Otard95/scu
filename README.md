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

## Utilities

<details>
<summary>

### String Builder

</summary>

The string builder is in a sense a dynamic array of chars.
It manages its own memory in the `.buf` field, and can be consered to own the
memory.

It allows for the user to supply their own memory allocation functions.
Specifically `malloc`, `realloc` and `free` via the `SCU_SB_MALLOC`,
`SCU_SB_REALLOC` and `SCU_SB_FRE` macros respectively.

<table>
<tr>
<td>Implementation def</td>
<td>Struct</td>
</tr>
<tr>
<td>

`SCU_SB_IMPLEMENTATION`

</td>
<td>

```c
typedef struct {
  char *buf;
  size_t len;
  size_t capacity;
} Scu_String_Builder;
```

</td>
</tr>
</table>

#### Functions

| Signature                                                                    | Description                                                            |
|------------------------------------------------------------------------------|------------------------------------------------------------------------|
| `bool scu_sb_append(Scu_String_Builder *sb, const char *str, size_t length)` | Appends `length` characters from `str` to the builder                  |
| `bool scu_sb_append_cstr(Scu_String_Builder *sb, const char *str)`           | Appends c-string to the builder without the null terninater            |
| `bool scu_sb_append_char(Scu_String_Builder *sb, char c)`                    | Appends a single char to the builder                                   |
| `char *scu_sb_to_cstr(Scu_String_Builder *sb)`                               | Makes sure the its buffer is null terminated and returns ptr to buffer |
| `void scu_sb_free(Scu_String_Builder *sb)`                                   | Frees the internal buffer                                              |

</details>
