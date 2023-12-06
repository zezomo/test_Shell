#!/bin/bash
git pull
echo "Enter commit"
read x
git add .
git commit -m "${x}"
git push
