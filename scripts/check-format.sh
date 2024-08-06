#!/bin/bash
set -eu

readonly scriptpath=$0;
readonly scriptdir=$(dirname $0)
readonly srcdir=$scriptdir/../cxx/lbm
readonly testdir=$scriptdir/../test/cxx

. $scriptdir/clang-format-env.sh

function main(){
    check_files $srcdir
    check_files $testdir
}

function check_file(){
    local inpfile=$1; shift
    local tmpfile=$(mktemp)
    /usr/bin/clang-format --style=file $inpfile > $tmpfile
    if [[ $(diff -q $inpfile $tmpfile) ]]
    then
        echo "format errors found in $inpfile"
        exit 1

        rm $tmpfile
    fi
    rm -f $tmpfile
}

function check_files(){
    local inpdir=$1; shift
    local source_files=$(find $inpdir -type f -regex ".*\\.hpp\\|.*\\.cpp" -not -regex ".*/\\.git/.*\\|.*/build.*")
    for source_file in $source_files
    do
        if [[ -f "$source_file" ]]
        then
            check_file $source_file
        fi
    done

}


main
