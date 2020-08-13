# meta-ipsum

Lorem Ipsum generator with a self-referential dictionary

## Installation

```bash
make && sudo make install
```

## Usage

```
Usage: meta-ipsum [-w,--word (<count>)]
                  [-s,--sentence (<count>)]
                  [-p,--paragraph (<count>)]
                  [-h]
```

## Explanation

Lorem Ipsum is random, nonsensical placeholder text used by designers to show text in designs in a way that it is not distracting, or if the actual text has not been provided yet.

Its dictionary consists of Latin words from a work by Cicero. The dictonary for `meta-ipsum` is derived from the very source code that generates it.

For example:

```c
#include <stdio.h>

int main() {
    printf("Hello, World!\n");

    return 0;
}
```

Would become:

```
include stdio int main printf hello world return
```
