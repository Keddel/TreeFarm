#!/bin/sh

./pull.sh
git add --all
git commit -am "autosave"
git push
