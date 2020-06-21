# Simple Unexpected Handler

This is a reasonable replacement for assert macros for large
software projects with substantial field deployments.

It will be also beneficial for smaller projects but the gain will be
less noticeable, see below (*)

# Problems with Unexpected Condition Handling

What options do we have to handle unexpected condition,
starting from unexpected parameter values and to unexpected
combination of external events, or unexpected timing?

For example, if we know that event A always happen before event B,
then there is no point of handling cases where B happen before A.
However, in the convoluted world of big long running software projects
nobody could be 100% sure.

## Asserts PROs and CONs

One can use assert macro

PROs:

1. Universal availability.
2. Light development-time weight.
3. Even way overloaded qa workers cannot ignore asserts.
4. Asserts normally produce cores that provide good level
   of debugging information.
5. Unit-test friendly.

CONs:

1. If we ship with asserts compiled in we risk crashes in the field.
2. If we ship asserts compiled out:
* We risk unhandled unexpected events.
* We have no chance to learn that there are such events.
* We break 'we test what we ship' principle.
* Requires really good release management to recompile each every
  corner of the code base with NDEBUG.


It seems that the only acceptable usage for asserts is shipping with asserts
compiled with limited field distribution. (*)

For example, the target is a single
complex web-site - it is acceptable to have some crashes in production: the
host standby will take over without substantial customer traffic disruption,
developers have a chance to fix it quickly.


## Traditional Log Messages PROs and CONs

There are traditional log messages

PROs:

1. Universal availability.
2. We will provide minimal handling for unexpected events.
3. We can learn about unexpected events by analyzing customer logs.
4. We test what we ship.

CONs:

1. Large software entities emit 1000s of log messages during tests
   the logs are mostly ignored by overloaded qa workers.
2. Logs do not provide enough information to debug a complex
   problem due to its universal nature.
3. High development time weight (lot more typing than assert).

It seems that CONs make traditional log messages unsuitable
for unexpected event handling.

## Syslog PROs and CONS

Then there is a syslog.

PROs:

1. Syslog could be run-time configured to crash program on errors,
   so overloaded qa workers would not be able to ignore them.
2. When configured to crash on error, it generate cores that provide good
   level of debugging information.
3. We will provide minimal handling for unexpected events.
4. We can learn about unexpected events by analyzing customer logs.
5. We test what we ship.

CONs:

1. It is awkward to use syslog just to report unexpected events,
   and it has heavy run-time weight when used for general
   logging.
2. Not universally available.
3. It is easy to mis-configure 'crash-on-error' feature during tests.
4. High development time weight (lot more typing than assert).
5. Syslog (when not crashing on error) does not provide enough information
   sufficient to debug a complex problem due to its universal nature.

So while the syslog is usable for the purpose, but it has its own down side.


# The Simple Unexpected Handler

It consists of run-time configurable handler function that can perform any
desired operation or combination of several applications: abort (this is
the default), log, syslog, dump extended information (e.g. stack trace),
raise support event, trigger dynamic core collection.

The invocation is packed into a single macro 'UXP()', this macro is for
abbreviation only, it is always compiled in.

In production environment we install handlers that do not cause crashes.

PROs:

1. Universal availability (just copy one file from this repository).
2. Light development-time weight.
3. Even way overloaded qa workers cannot ignore aborts that are the default
   handler action.
4. Aborts normally produce cores that provide good level
   of debugging information.
5. Unit-test friendly.
6. We will provide minimal handling for unexpected events.
7. We can learn about unexpected events by analyzing information
   collected from the field.
8. The handler is intended to handle rare unexpected events,
   so it can be made to collect a lot of information.
9. We test what we ship.


CONs:

None


# Files

For completeness we implement it in ANSI-C because
it does not require c++ run-time and could be used in both
c++ and c-.

simple_unexpected_handler.c
simple_unexpected_handler.h

# Usage

The most trivial use:

    ...
    if (!expected_condition()) {
      UXP();
      return false;
    }
    ...

Other uses are self explanatory.
