#ifndef SCU_STRING_BUILDER_H
#define SCU_STRING_BUILDER_H

#include <stdbool.h>
#include <string.h>

// Allow user to set their own allocator
#ifndef SCU_SB_MALLOC
#define SCU_SB_MALLOC malloc
#endif
#ifndef SCU_SB_REALLOC
#define SCU_SB_REALLOC realloc
#endif
#ifndef SCU_SB_FREE
#define SCU_SB_FREE free
#endif

typedef struct {
  char *buf;
  size_t len;
  size_t capacity;
} Scu_String_Builder;

bool scu_sb_append(Scu_String_Builder *sb, const char *str, size_t length);
bool scu_sb_append_cstr(Scu_String_Builder *sb, const char *str);
bool scu_sb_append_char(Scu_String_Builder *sb, char c);
char *scu_sb_to_cstr(Scu_String_Builder *sb);
void scu_sb_free(Scu_String_Builder *sb);

#endif // SCU_STRING_BUILDER_H

#ifdef SCU_SB_IMPLEMENTATION

bool scu_sb_append(Scu_String_Builder *sb, const char *str, size_t length) {
  if (sb->len + length > sb->capacity) {
    sb->capacity = sb->capacity + (sb->capacity >> 1) + length;
    sb->buf = (char*) SCU_SB_REALLOC(sb->buf, sb->capacity);
    if (!sb->buf) {
      return false;
    }
  }
  memcpy(sb->buf + sb->len, str, length);
  sb->len += length;
  return true;
}

bool scu_sb_append_cstr(Scu_String_Builder *sb, const char *str) {
  return scu_sb_append(sb, str, strlen(str));
}

bool scu_sb_append_char(Scu_String_Builder *sb, char c) {
  return scu_sb_append(sb, &c, 1);
}

char *scu_sb_to_cstr(Scu_String_Builder *sb) {
  if (sb->buf[sb->len - 1] != '\0') {
    if (!scu_sb_append_char(sb, '\0')) return NULL;
  }
  return sb->buf;
}

void scu_sb_free(Scu_String_Builder *sb) {
  SCU_SB_FREE(sb->buf);
}

#endif // SCU_SB_IMPLEMENTATION
