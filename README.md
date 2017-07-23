# Module Down

[![Build Status](https://travis-ci.org/TimSimpson/ModDown.svg?branch=master)](https://travis-ci.org/TimSimpson/ModDown)
[![Build status](https://ci.appveyor.com/api/projects/status/hro698ynw2t40014?svg=true)](https://ci.appveyor.com/project/TimSimpson/ModDown)

This is an opionated tool for documenting projects the way I like to write them as large Mark Down files.

## Building

This library is built with CMake, and tries to adhere to the some rules described in [The Ultimate Guide to Modern CMake](https://rix0r.nl/blog/2015/08/13/cmake-guide/). Specifically effort is made to avoid trying to find it's own dependencies so that they can be specified by a parent project instead.

For an example of what this looks like please see [the parent project used for CI](standalone/CMakeLists.txt).

### Dependencies / Requirements

* The [Guideline Support Library](https://github.com/Microsoft/GSL), defined as the imported interface library `gsl`.
* [The Boost libraries](http://www.boost.org/) (header only) must be defined as the imported interface library `boost`.
* [Boost File System](http://www.boost.org/doc/libs/1_64_0/libs/filesystem/doc/index.htm) Must be defined as `lp3_deps::boost_filesystem`.
* [Catch](https://github.com/philsquared/Catch), defined as the imported interface library `catch`.