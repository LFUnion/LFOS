#!/bin/bash

astyle --style=java --break-blocks --delete-empty-lines --remove-brackets --break-after-logical --max-code-length=80 --suffix=none --recursive "kernel/*.c"

astyle --style=java --break-blocks --delete-empty-lines --remove-brackets --break-after-logical --max-code-length=80 --suffix=none --recursive "kernel/*.h"
