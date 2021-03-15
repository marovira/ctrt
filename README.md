# CTRT

> A Compile-Time Ray Tracer

[![Generic badge](https://img.shields.io/badge/License-BSD3-blue)](LICENSE)
[![Generic badge](https://img.shields.io/badge/Language-C++17-red.svg)](https://en.wikipedia.org/wiki/C%2B%2B17)
[![CodeFactor](https://www.codefactor.io/repository/github/marovira/ctrt/badge)](https://www.codefactor.io/repository/github/marovira/ctrt)
[![Build Status](https://travis-ci.org/marovira/ctrt.svg?branch=master)](https://travis-ci.org/marovira/ctrt)
[![Build status](https://ci.appveyor.com/api/projects/status/qk8lbpldkada6xl6?svg=true)](https://ci.appveyor.com/project/marovira/ctrt)

## What is CTRT?

CTRT (short for **C**ompile-**T**ime **R**ay **T**racing) is a relatively simple
ray tracer designed to perform *all* computations at compile-time without using
template metaprogramming. Instead, CTRT relies on C++17 `constexpr` functions to
generate the final image.

It is loosely based on Peter Shirley's [Ray Tracing in One
Weekend](https://raytracing.github.io/) with some ideas taken from Kevin
Suffern's *Ray Tracing from the Ground Up*. 

## Results

Last render performed:

![render](https://github.com/marovira/ctrt/blob/master/render.jpg)

## Performance

All tests were performed on a PC running Windows 10 64-bit with an AMD Ryzen 9
3900X processor and 64 GB of RAM. The code was compiled using MSVC 16.8.5. The
comparisons were performed by generating the image both at runtime and compile
time. All tested images are 512x512 and can be found in the `test_images`
directory. Results are as follows:

| Test | Runtime | Compile-time |
|------|---------|--------------|
| test_01 | 14.305 ms | 19m 35s |

## Dependencies

The following are **core** dependencies of CTRT:

* CMake 3.19+
* A C++17 compiler.

CTRT has been tested on the following platforms and compilers:

| Platform (Compiler) | Version |
|---------------------|---------|
| Windows (MSVC) | 19.28 |
| Linux (GCC) | 9.3 |
| Linux (Clang) | 9.0 |

As with most of my projects, macOS is **not** supported.

In addition, CTRT depends on the following libraries:

* [Zeus](https://github.com/marovira/zeus)

## License

CTRT is published under the BSD-3 license and can be viewed
[here](https://github.com/marovira/ctrt/blob/master/LICENSE)
