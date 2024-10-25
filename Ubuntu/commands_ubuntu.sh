export ubuntu_container_name=ubuntu_opencascade_base

function build_opencascade_ubuntu_base()
{
    cd $OpenCascade_Folder/Ubuntu
    docker build \
        --build-arg DOCKER_USER_NAME=$(whoami) \
        --build-arg DOCKER_USER_ID=$(id -u) \
        --build-arg DOCKER_GROUP_NAME=$(whoami) \
        --build-arg DOCKER_GROUP_ID=$(id -g) \
        --tag ${ubuntu_container_name} .
}

function run_opencascade_ubuntu_base()
{
    docker run -it ${ubuntu_container_name} /bin/bash
}
