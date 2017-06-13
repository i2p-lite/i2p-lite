# i2p-lite

I2P Network protocol implementation in C99


## Status

Non Functional work-in-progress, come back in a year or two for something serious.

See the project roadmap [here](ROADMAP.md)

## Project Outline

**(goal):** Full Interoperation with mainline I2P Network.

**(goal):** Clean, concise, documented, readable source code is not optional in this project.

**(goal):** Performance is just as important as Security, compromising either for the other is not going to happen.

**(goal):** Able to run easily on a SOHO Router or RPI 1.

**(goal):** Available in Debian Stable, one day, probably.

**(goal):** Casual and Semi-Civil Dev Community for cool people to make cool things.

**(non-goal):** emscripten / [ insert cryptocoin here ] / YC-Pet-Project-of-the-Month integration.

**(non-goal):** Support for Docker or anything related to or depending on Docker.

**(non-goal):** Funding / Backing / Support from Corporate or Governmental Entities.

**(non-goal):** Project Censorship. *[1]*

## Requirements

* C11 compatible compiler
* CMake 3.x
* libuv 1.x
* libssl 1.x
* jemalloc

## Supported Platforms

The initial platforms to be supported are

* Linux (x86_64 and ARMv6)
* FreeBSD (x86_64 only)
* MacOS x86_64

If your Platform is not currently supported don't wait for someone else to add it as otherwise it'll probably never get done.


*[1]* If anyone hurts your feelings or disagrees with your political views talk about it on your personal blog instead of making a bug report. In the future we may have a repository just for documenting these (non-)bug reports for my own personal amusement and for future historians to study.
