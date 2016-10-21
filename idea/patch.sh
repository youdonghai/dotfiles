#! /bin/sh

if [ "$#" -ne 1 ]; then
  echo "Usage: $0 path_to_ide" >&2
  exit 1
fi

path_to_ide=$1

jar uf ${path_to_ide}/lib/pycharm.jar com/intellij/openapi/keymap/impl/*
mv terminal_old org
jar uf ${path_to_ide}/plugins/terminal/lib/terminal.jar org/jetbrains/plugins/terminal/*
mv org terminal_old

grep 'emitFirstKeystrokeWhenTimeout' ${path_to_ide}/bin/idea.properties
OUT=$?
if [ $OUT -eq 1 ]
then
    cat ./idea.properties >> ${path_to_ide}/bin/idea.properties
fi
