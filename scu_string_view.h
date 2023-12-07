#ifndef SCU_STRING_VIEW_H
#define SCU_STRING_VIEW_H

#include <stdbool.h>
#include <string.h>

typedef struct {
  const char *buf;
  size_t len;
} Scu_String_View;

// Constructors
Scu_String_View scu_sv_from_cstr(const char *str);
Scu_String_View scu_sv_from_buffer(const char *buffer, size_t length);

bool scu_sv_eq(Scu_String_View sv1, Scu_String_View sv2);
Scu_String_View scu_sv_trim_right(Scu_String_View sv);
Scu_String_View scu_sv_trim_left(Scu_String_View sv);
Scu_String_View scu_sv_trim(Scu_String_View sv);

#endif // SCU_STRING_VIEW_H

#ifdef SCU_SV_IMPLEMENTATION

Scu_String_View scu_sv_from_cstr(const char *str) {
  Scu_String_View sv;
  sv.buf = str;
  sv.len = strlen(str);
  return sv;
}

Scu_String_View scu_sv_from_buffer(const char *buffer, size_t length) {
  Scu_String_View sv;
  sv.buf = buffer;
  sv.len = length;
  return sv;
}

bool scu_sv_eq(Scu_String_View sv1, Scu_String_View sv2) {
  if (sv1.len != sv2.len) return false;
  return memcmp(sv1.buf, sv2.buf, sv1.len) == 0;
}

bool scu_is_whitespace(char c) {
  static const char *whitespace = " \t\n\r ";
  return strchr(whitespace, c) != NULL;
}

Scu_String_View scu_sv_trim_right(Scu_String_View sv) {
  Scu_String_View sv_out = {0};
  size_t i = sv.len;
  while (i > 0 && scu_is_whitespace(sv.buf[i - 1])) {
    i--;
  }
  sv_out.buf = sv.buf;
  sv_out.len = i;
  return sv_out;
}

Scu_String_View scu_sv_trim_left(Scu_String_View sv) {
  Scu_String_View sv_out = {0};
  size_t i = 0;
  while (i < sv.len && scu_is_whitespace(sv.buf[i])) {
    i++;
  }
  sv_out.buf = sv.buf + i;
  sv_out.len = sv.len - i;
  return sv_out;
}

Scu_String_View scu_sv_trim(Scu_String_View sv) {
  return scu_sv_trim_left(scu_sv_trim_right(sv));
}

#endif
