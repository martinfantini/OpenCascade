#!/usr/bin/env bash

export OpenCascade_Folder=/lhome/martin.fantini/Projects/OpenCascade

test -f $OpenCascade_Folder/Ubuntu/commands_ubuntu.sh && source $OpenCascade_Folder/Ubuntu/commands_ubuntu.sh
test -f $OpenCascade_Folder/Ubuntu_Tests/Container/commands_ubuntu.sh && source $OpenCascade_Folder/Ubuntu_Tests/Container/commands_ubuntu.sh


test -f $OpenCascade_Folder/WebAssembly/commands_web_assembly.sh && source $OpenCascade_Folder/WebAssembly/commands_web_assembly.sh
test -f $OpenCascade_Folder/WebAssembly_Tests/Container/commands_web_assembly.sh && source $OpenCascade_Folder/WebAssembly_Tests/Container/commands_web_assembly.sh
