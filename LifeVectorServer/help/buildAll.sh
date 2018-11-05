#!/bin/bash

for f in *.sh; do  # or wget-*.sh instead of *.sh
    if [[ "$f" != "buildAll.sh" ]]; then
        bash ./$f || break # if needed
    fi
done
