#!/bin/sh

CURRENT_DIRECTORY=$(cd `dirname $0` && pwd)

if [[ "$#" != "1" ]];
then
   echo "Expected single argument: data file."
   exit
fi

cat $1 | $CURRENT_DIRECTORY/jabberhive-cli /tmp/jh0
