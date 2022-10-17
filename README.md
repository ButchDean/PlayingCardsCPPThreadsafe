# PlayingCardsCPP (Thread Safe)

Thread Safe C++ version of my [C++ playing cards code](https://github.com/ButchDean/PlayingCardsCPP "Playing Cards (Non-Thread Safe)").

Performs required card functionality like dealing and shuffling that can be part of any game. The deck may be reshuffled at any point, irrespective of the remaining cards in the deck.

The specific value of the card is also given and can be set.

Last but not least, minimal use of slow strings is used making this a faster solution.

To clone this repo do:
```
git clone --recurse-submodules git@github.com:ButchDean/PlayingCardsCPPThreadsafe.git
```
To build do:
```
$ cmake -S . -B build
$ cmake --build build
```
And to run the program do:
```
$ build/pcts
```
And to run unit tests do:
```
$ cd build/PlayingCardsCore****
$ ctest
```
## Supported Platforms

* Mac OS
* Linux (coming up)

Windows support is not planned at this time. It should be easy enough to import the .cc and .h files into a Visual Studio Console Application, but I have not checked since I only have Mac and Linux machines.