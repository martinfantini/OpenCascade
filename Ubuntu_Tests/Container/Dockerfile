
FROM ubuntu_opencascade_base:latest

ARG DOCKER_USER_NAME=default_user

USER root

RUN apt-get install -y libopenmpi-dev libhdf5-serial-dev mpi
RUN apt-get install -y libvtk9-qt-dev libglfw3 libglfw3-dev x11-apps

ENV LD_LIBRARY_PATH="${LD_LIBRARY_PATH}:${OPT_DIR}/opencascade-${OCCT_VERSION}-Release/lib"

# Copy the open cascade tests
RUN cp -r ${OPT_DIR}/opencascade-${OCCT_VERSION}/samples/glfw /home/${DOCKER_USER_NAME}/
WORKDIR /home/${DOCKER_USER_NAME}/glfw
RUN cmake -S . -B ./build \
        -DOpenCASCADE_DIR:PATH=${OPT_DIR}/opencascade-${OCCT_VERSION}-Release/lib/cmake/opencascade
WORKDIR /home/${DOCKER_USER_NAME}/glfw/build
RUN make -j$(nproc)

#USER ${DOCKER_USER_NAME}
WORKDIR /home/${DOCKER_USER_NAME}/QT-VTK-OpenCascade/

# To compile the code inside this folder
#RUN cmake -S . -B ./build  \
#    -DINSTALL_DIR=${OPT_DIR}/QT-VTK-OpenCascade-Release \
#    -DCMAKE_BUILD_TYPE:STRING="Release" \
#    -DOpenCascade_DIR:PATH=${OPT_DIR}/opencascade-${OCCT_VERSION}-Release/lib/cmake/opencascade


# ENV LD_LIBRARY_PATH=/usr/lib/x86_64-linux-gnu/:${LD_LIBRARY_PATH}

WORKDIR /home/${DOCKER_USER_NAME}/QT-VTK-OpenCascade/build
