#!/bin/bash

if [[ $1 = "f" ]]
then
	./scripts/doit unixcompile play -Ofast $2 $3 $4 $5 $6 $7 $8 $9
elif [[ $1 = "mine" ]]
then
	./scripts/doit unixcompile play $2 $3 $4 $5 $6 $7 $8 $9
else
	./scripts/doit unixcompile play -g $*
fi

exit

