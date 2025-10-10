/*
 * Created by helmholtz on 10/10/2025
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>

struct stream {
  unsigned char *buffer;
  int size;
  int pos;
};

int stream_eof(const struct stream *stream);
int stream_getc(struct stream *stream);
void stream_revert(struct stream *stream);
int stream_leftbyte(struct stream *stream);
int stream_read(void *buf, size_t size, size_t nitems, struct stream *stream);
char *stream_gets(char *buf, size_t n, struct stream *stream);
struct stream *create_stream(FILE *file);
