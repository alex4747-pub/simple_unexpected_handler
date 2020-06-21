//
// Copyright (C) 2020  Aleksey Romanov (aleksey at voltanet dot io)
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

#include <simple_unexpected_handler.h>
#include <cassert>
#include <csignal>
#include <iostream>

static int signal_counter;
static int handler1_counter;
static int handler2_counter;

static void signal_handler(int signo) {
  assert(signo == SIGABRT);
  assert(signal_counter == 0);
  assert(handler1_counter == 1);
  assert(handler2_counter == 1);
  std::cout << "signal_handler: called\n";
  signal_counter++;

  // We should not return
  exit(0);
}

static void handler1(char const* file, int line) {
  std::cout << "handler1: file: " << file << " line: " << line << "\n";
  handler1_counter++;
}

static void handler2(char const* file, int line) {
  std::cout << "handler2: file: " << file << " line: " << line << "\n";
  handler2_counter++;
}

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;

  std::signal(SIGABRT, signal_handler);

  assert(handler1_counter == 0);
  assert(handler2_counter == 0);

  void (*prev)(char const*, int) = UXP_SET_HANDLER(handler1);

  assert(prev == NULL);

  // Raise unexpected event
  //
  UXP();
  assert(handler1_counter == 1);
  assert(handler2_counter == 0);

  // Update handler
  //
  prev = UXP_SET_HANDLER(handler2);

  assert(prev == handler1);

  // Raise unexpected event
  UXP();
  assert(handler1_counter == 1);
  assert(handler2_counter == 1);

  // Reset handler to default
  prev = UXP_SET_HANDLER(nullptr);

  assert(prev == handler2);

  // Raise unexpected event
  UXP();

  // Signal should be caught and signal handler should
  // exit from the program
  //
  assert(false);

  return 1;
}
