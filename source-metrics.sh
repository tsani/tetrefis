#!/bin/bash

# Shows the unique lines of code in each source file.

for f in *.c *.h ; do
    echo $(sort -u "$f" | wc -l) "$f"
done |
    sort -n
