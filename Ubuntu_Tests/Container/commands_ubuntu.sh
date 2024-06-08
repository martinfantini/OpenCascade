export ubuntu_container_name=ubuntu_opencascade_tests

function build_opencascade_ubuntu_tests()
{
    cd $OpenCascade_Folder/Ubuntu_Tests/Container
    docker build --tag ${ubuntu_container_name} .
}

function run_opencascade_ubuntu_tests()
{
    xhost +
    docker run \
        --user $(id -u) \
        -v /home/rmfantini/Projects/OpenCascade_Tests/Ubuntu_Tests/QT-VTK-OpenCascade:/opt/QT-VTK-OpenCascade \
        -v /home/rmfantini/Projects/OpenCascade_Tests/Ubuntu_Tests/VTK_OpenCascasde:/opt/VTK_OpenCascasde \
        -v /tmp/.X11-unix:/tmp/.X11-unix \
        -e DISPLAY=$DISPLAY \
        -it ${ubuntu_container_name} /bin/bash 
    xhost -
}
