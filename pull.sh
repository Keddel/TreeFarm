#!/bin/bash

# Ensure upstream
git remote add upstream git@gitlab.cs.wallawalla.edu:cptr142/student142_project3.git 2> /dev/null

# Pull changes
git pull --no-edit
git fetch upstream
git checkout master
git merge upstream/master -m "automerging"
