
FROM ubuntu_opencascade_base:latest

RUN apt-get install -y libopenmpi-dev libhdf5-serial-dev mpi
RUN apt-get install -y libvtk9-qt-dev libglfw3 libglfw3-dev

ENV LD_LIBRARY_PATH="${LD_LIBRARY_PATH}:${OPT_DIR}/opencascade-${OCCT_VERSION}-Release/lib"

WORKDIR ${OPT_DIR}/QT-VTK-OpenCascade/

# To compile the code inside this folder
#RUN cmake -S . -B ./build  \
#    -DINSTALL_DIR=${OPT_DIR}/QT-VTK-OpenCascade-Release \
#    -DCMAKE_BUILD_TYPE:STRING="Release" \
#    -DOpenCascade_DIR:PATH=${OPT_DIR}/opencascade-${OCCT_VERSION}-Release/lib/cmake/opencascade

WORKDIR ${OPT_DIR}/QT-VTK-OpenCascade/build
WORKDIR ${OPT_DIR}/QT-VTK-OpenCascade

RUN cp -r ${OPT_DIR}/opencascade-${OCCT_VERSION}/samples/glfw /home/ubuntu/

WORKDIR /home/ubuntu/glfw
RUN cmake -S . -B ./build \
        -DOpenCASCADE_DIR:PATH=${OPT_DIR}/opencascade-${OCCT_VERSION}-Release/lib/cmake/opencascade

WORKDIR /home/ubuntu/glfw/build
RUN make -j$(nproc)
