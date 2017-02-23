Debian Bug report logs - #854054
icoutils: CVE-2017-6010 CVE-2017-6011

version graph
Package: icoutils; Maintainer for icoutils is Colin Watson <cjwatson@debian.org>; Source for icoutils is src:icoutils.
Reported by: "op7ic \\x00" <op7ica@gmail.com>
Date: Fri, 3 Feb 2017 13:30:01 UTC
Severity: grave
Tags: security, upstream
Found in versions icoutils/0.31.1-1, 0.31.1

Machine: x86_64
OS: linux-gnu
Compiler: gcc
Compilation CFLAGS: "-ggdb3 -O0"
Machine Type: x86_64-unknown-linux-gnu
icoutils Version: 0.31.1
Release Status: release
Author: Jerzy Kramarz

A buffer overflow was observed in "extract_icons" function in "extract.c" source file. 
This issue can be triggered by processing a corrupted ico file and will result in icotool crash.


An out-of-bound read leading to buffer overflow was observed in "simple_vec" function in "extract.c" source file. 
This issue can be triggered by processing a corrupted ico file and will result in icotool crash. 
