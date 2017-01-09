#! /bin/sh

if [ "$#" -ne 1 ]; then
  echo "Usage: $0 path_to_ide" >&2
  exit 1
fi

path_to_ide=$1

jar uf ${path_to_ide}/lib/idea.jar com/intellij/openapi/keymap/impl/*
jar uf ${path_to_ide}/plugins/terminal/lib/terminal.jar org/jetbrains/plugins/terminal/*

grep 'emitFirstKeystrokeWhenTimeout' ${path_to_ide}/bin/idea.properties
OUT=$?
if [ $OUT -eq 1 ]
then
    cat ./idea.properties >> ${path_to_ide}/bin/idea.properties
fi
