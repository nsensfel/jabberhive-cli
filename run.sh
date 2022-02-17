#!/bin/bash

CURRENT_DIRECTORY=$(cd `dirname $0` && pwd)

find /my/jabberhive/dataset -name "*.txt" |  parallel -j4 $CURRENT_DIRECTORY/learn.sh {}
