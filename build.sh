#!/bin/bash

pushd `dirname $0` > /dev/null
SRC_DIR=`pwd`
popd > /dev/null

OUT_DIR=$1
if [ -z "$OUT_DIR" ]; then
    OUT_DIR=`mktemp -d -t build.XXXXXXXX`
    CLEANUP=yes
else
    mkdir -p $OUT_DIR
    CLEANUP=no
fi

if [ ! -d "$OUT_DIR" ]; then
    echo "$OUT_DIR is not a valid directory"
    exit 1
fi

rm -rf $OUT_DIR
mkdir $OUT_DIR
cd $OUT_DIR

CODE=0

if cmake $SRC_DIR; then
    if make clean; then
        if make; then
            if make test; then
                CODE=0
            else
                cat $OUT_DIR/Testing/Temporary/LastTest.log
                CODE=4
            fi
        else
            CODE=3
        fi
    else
        CODE=2
    fi
else
    CODE=1
fi

if [ "$CLEANUP" == "yes" ]; then
    rm -rf $OUT_DIR
fi

exit $CODE
