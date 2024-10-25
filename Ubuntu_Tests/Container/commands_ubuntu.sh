export test_ubuntu_container_name=ubuntu_opencascade_tests

function build_opencascade_ubuntu_tests()
{
    cd $OpenCascade_Folder/Ubuntu_Tests/Container
    docker build  \
        --build-arg DOCKER_USER_NAME=$(whoami) \
        --tag ${test_ubuntu_container_name} .
}

function run_opencascade_ubuntu_tests_user()
{
    echo "This container does not work because it neeed root access to the libraries and to the X11 video"
    xhost +local:*
    docker run \
        --user $(whoami) \
        -v ${OpenCascade_Folder}/Ubuntu_Tests/QT-VTK-OpenCascade:/home/$(whoami)/QT-VTK-OpenCascade \
        -v /tmp/.X11-unix:/tmp/.X11-unix \
        -e DISPLAY=$DISPLAY \
        -it ${test_ubuntu_container_name} /bin/bash 
    xhost -local:*
}

function run_opencascade_ubuntu_tests_root()
{
    xhost +local:*
    docker run \
        --user $(whoami) \
        -v ${OpenCascade_Folder}/Ubuntu_Tests/QT-VTK-OpenCascade:/home/$(whoami)/QT-VTK-OpenCascade \
        -v /tmp/.X11-unix:/tmp/.X11-unix \
        -e DISPLAY=$DISPLAY \
        -it ${test_ubuntu_container_name} /bin/bash 
    xhost -local:*
}
