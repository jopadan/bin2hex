#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([bin2hex], [1.0], [jondaniel879@gmail.com])
AC_COPYRIGHT([(C) 2019 Jon Daniel <jondaniel879@gmail.com>])
AC_CONFIG_SRCDIR([bin2hex.c])
AC_CONFIG_HEADERS(config.h)
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CC_C99
AC_PROG_MAKE_SET
AM_MAINTAINER_MODE
# Checks for libraries.
AC_CHECK_HEADERS([stdlib.h stdio.h stdint.h string.h error.h errno.h sys/stat.h unistd.h])


AC_CONFIG_FILES([Makefile])

AC_OUTPUT
