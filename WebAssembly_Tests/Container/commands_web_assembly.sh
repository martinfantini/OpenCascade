#!/usr/bin/env bash

export webassembly_container_test_name=webassembly_opencascade_tests

function build_opencascade_webassembly_tests()
{
    cd $OpenCascade_Folder/WebAssembly_Tests/Container
    cp $OpenCascade_Folder/WebAssembly_Tests/Test_Webgl/CMakeLists.txt .
    docker build --tag ${webassembly_container_test_name} .
    rm CMakeLists.txt
}

function run_opencascade_webassembly_tests_root()
{
    docker run  \
        --name ${webassembly_container_test_name} \
        -p 7000:7000 ${webassembly_container_test_name}
}

function run_opencascade_webassembly_tests_user()
{
    echo "This container does not work because it neeed root access to the libraries"
    docker run  \
        --user $(whoami) \
        --name ${webassembly_container_test_name} \
        -p 7000:7000 ${webassembly_container_test_name}
}

function stop_opencascade_webassembly_tests()
{
    docker stop ${webassembly_container_test_name}
}
