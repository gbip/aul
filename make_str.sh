#!/bin/bash
xxd -c 6 $1 | cut -d' ' -f2-4 | sed 's/ //g'
