#!/bin/bash
pandoc ../README.md --template eisvogel.tex -o rapport.pdf --from markdown --listings -V lang=fr
