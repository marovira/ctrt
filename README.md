# CTRT

> A Compile-Time Ray Tracer

[![Generic badge](https://img.shields.io/badge/License-BSD3-blue)](LICENSE)
[![Generic badge](https://img.shields.io/badge/Language-C++17-red.svg)](https://en.wikipedia.org/wiki/C%2B%2B17)
[![Clang](https://github.com/marovira/ctrt/actions/workflows/clang.yml/badge.svg)](https://github.com/marovira/ctrt/actions/workflows/clang.yml)
[![GCC](https://github.com/marovira/ctrt/actions/workflows/gcc.yml/badge.svg)](https://github.com/marovira/ctrt/actions/workflows/gcc.yml)
[![MSVC](https://github.com/marovira/ctrt/actions/workflows/msvc.yml/badge.svg)](https://github.com/marovira/ctrt/actions/workflows/msvc.yml)
[![CodeFactor](https://www.codefactor.io/repository/github/marovira/ctrt/badge)](https://www.codefactor.io/repository/github/marovira/ctrt)

## What is CTRT?

CTRT (short for **C**ompile-**T**ime **R**ay **T**racing) is a relatively simple
ray tracer designed to perform *all* computations at compile-time without using
template metaprogramming. Instead, CTRT relies on C++17 `constexpr` functions to
generate the final image.

It is loosely based on Peter Shirley's [Ray Tracing in One
Weekend](https://raytracing.github.io/) with some ideas taken from Kevin
Suffern's *Ray Tracing from the Ground Up*.

> **Note:**
>
> I have a blog that describes how the ray tracer was designed. If you're
> interested, you can read about it
> [here](https://marovira.github.io/p/designing-a-compile-time-ray-tracer/)

## Results

Last render performed:

![render](https://github.com/marovira/ctrt/blob/master/render.jpg)

## Performance

Due to the fact that all computations are performed at compile-time, the ray
tracer utilises a significant amount of memory and takes a long time to perform
the render. All renders are performed was done on a PC running Windows 1- 64-bit
with an AMD Ryzen 9 3900X processor and 64 GB of RAM. With this setup, here are
the results for each generated image (they can be found in the `test_images`
directory):

| Scene | Time |
|------|-------|
| test_01 | 21m 6s |
| test_02 | 11m 43s |
| test_03 | 42m 4s |
| test_04 | 15m 33s |
| test_05 | 17m 31s |
| test_06 | 1m 3s * |

The final time was taken with the parallelised version of the ray tracer.

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
