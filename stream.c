/*
 * Created by helmholtz on 10/10/2025
 */

#include "stream.h"
#include <stdio.h>
#include <string.h>

int stream_eof(const struct stream *stream) {
  return stream->pos >= stream->size ? 1 : 0;
}

int stream_getc(struct stream *stream) {
  if (stream_eof(stream))
    return EOF;
  return stream->buffer[stream->pos++];
}

void stream_revert(struct stream *stream) {
  if (stream->pos > 0)
    stream->pos--;
}

int stream_leftbyte(struct stream *stream) {
  return stream->size - stream->pos;
}

int stream_read(void *buf, size_t size, size_t nitems, struct stream *stream) {
  int items_available = (stream->size - stream->pos) / size;
  int items_count = items_available > (int)nitems ? nitems : items_available;
  memcpy(buf, stream->buffer + stream->pos, size * items_count);
  stream->pos += items_count * size;
  return items_count * size;
}

char *stream_gets(char *buf, size_t n, struct stream *stream) {
  size_t i;
  for (i = 0; i < n - 1; i++) {
    int c = stream_getc(stream);
    if (c == EOF) {
      if (i == 0)
        return NULL;
      break;
    }
    buf[i] = c;
    if (c == '\n') {
      i++;
      break;
    }
  }
  buf[i] = '\0';
  return buf;
}

struct stream *create_stream(FILE *file) {
  if (file == NULL)
    return NULL;
  struct stream *s = malloc(sizeof(struct stream));
  fseek(file, 0, SEEK_END);
  s->size = ftell(file);
  fseek(file, 0, SEEK_SET);
  s->pos = 0;
  s->buffer = malloc(s->size);
  fread(s->buffer, 1, s->size, file);
  return s;
}
