/*
 * Copyright (C) 2020  Aleksey Romanov (aleksey at voltanet dot io)
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef SIMPLE_UNEXPECTED_HANDLER_H_
#define SIMPLE_UNEXPECTED_HANDLER_H_

/*
 * This ansi-c implementation of the simple
 * unexpected handler.
 */
#ifdef __cplusplus
extern "C" {
namespace simple {
#endif
void simple_unexpected_handler_event(const char* file, int line);

typedef void (*simple_unexpected_handler_t)(const char*, int);

simple_unexpected_handler_t simple_unexpected_handler_set(
    simple_unexpected_handler_t handler);

#ifdef __cplusplus
}
}

#define UXP() simple::simple_unexpected_handler_event(__FILE__, __LINE__)
#define UXP_SET_HANDLER(h) simple::simple_unexpected_handler_set(h)

#else

#define UXP() simple_unexpected_handler_event(__FILE__, __LINE__)
#define UXP_SET_HANDLER(h) simple_unexpected_handler_set(h)

#endif /* __cplusplus */

#endif /* SIMPLE_UNEXPECTED_HANDLER_H_ */
