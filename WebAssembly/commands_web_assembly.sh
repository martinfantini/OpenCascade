export emscripten_name_container_name=emscripten_opencascade_base

function build_opencascade_webassembly_base()
{
    cd $OpenCascade_Folder/WebAssembly
    docker build --tag ${emscripten_name_container_name} . 
}


function run_opencascade_webassembly_base()
{
    docker run -it ${emscripten_name_container_name} /bin/bash
}
