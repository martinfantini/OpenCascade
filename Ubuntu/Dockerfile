# download the data from the last emscripten
FROM ubuntu:24.04

ENV OPT_DIR /opt
ENV THIRDPARTY_DIR ${OPT_DIR}/3rdparty

ENV OCCT_VERSION 7_8_1
ENV DOCTEST_VERSION 2.4.11
ENV GMSH_VERSION 4_4_0
ENV OCC_CSG_VERSION 0.9.9.2
ENV NETEGEN_VERSION 6.2.2403

RUN apt-get clean && apt-get update

RUN apt-get install -y build-essential git wget vim cmake automake libtool autoconf p7zip-full p7zip-rar python3 python3-dev
RUN apt-get install -y tcllib tklib tcl-dev tk-dev libfreetype-dev libxt-dev libxmu-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev
RUN apt-get install -y libfreeimage-dev libtbb-dev libgl2ps-dev libvtk9-dev cmake-curses-gui rapidjson-dev libdraco-dev libx11-dev
RUN apt-get install -y qtcreator qt5-qmake qtbase5-dev

WORKDIR ${OPT_DIR}
RUN git clone https://github.com/Open-Cascade-SAS/OCCT.git opencascade-${OCCT_VERSION} && \
    cd opencascade-${OCCT_VERSION} && \
    git checkout tags/V${OCCT_VERSION} -b V${OCCT_VERSION}

WORKDIR ${OPT_DIR}/opencascade-${OCCT_VERSION}/build
WORKDIR ${OPT_DIR}/opencascade-${OCCT_VERSION}-Release
WORKDIR ${OPT_DIR}/opencascade-${OCCT_VERSION}
RUN cmake -S . -B ./build  \
    -DINSTALL_DIR:PATH=${OPT_DIR}/opencascade-${OCCT_VERSION}-Release  \
    -DCMAKE_BUILD_TYPE:STRING="Release" \
    -DUSE_TK:BOOL=ON \
    -DUSE_TCL:BOOL=ON \
    -DUSE_FREEIMAGE:BOOL=ON \
    -DUSE_FFMPEG:BOOL=OFF \
    -DUSE_RAPIDJSON:BOOL=ON \
    -DUSE_VTK:BOOL=ON \
    -DUSE_DRACO:BOOL=ON \
    -DUSE_GLES2:BOOL=OFF \
    -D3RDPARTY_TK_INCLUDE_DIR:PATH=/usr/include \
    -D3RDPARTY_TCL_INCLUDE_DIR=/usr/include \
    -D3RDPARTY_VTK_INCLUDE_DIR:PATH=/usr/include \
    -D3RDPARTY_DRACO_INCLUDE_DIR:PATH=/usr/include \
    -D3RDPARTY_DRACO_LIBRARY_DIR:PATH=/usr/lib/x86_64-linux-gnu \
    -D3RDPARTY_TCL_INCLUDE_DIR:PATH=/usr/include/tcl8.6 \
    -D3RDPARTY_TCL_LIBRARY_DIR:PATH=/usr/lib/x86_64-linux-gnu
 
WORKDIR ${OPT_DIR}/opencascade-${OCCT_VERSION}/build
RUN make -j$(nproc) install

WORKDIR ${OPT_DIR}
RUN git clone https://github.com/doctest/doctest.git doctest-v${DOCTEST_VERSION} && \
    cd doctest-v${DOCTEST_VERSION} && \
    git checkout tags/v${DOCTEST_VERSION} -b v${DOCTEST_VERSION}

WORKDIR ${OPT_DIR}
RUN git clone https://github.com/miho/OCC-CSG.git OCC-CSG-${OCC_CSG_VERSION} && \
    cd OCC-CSG-${OCC_CSG_VERSION} && \
    git checkout tags/v${OCC_CSG_VERSION} -b v${OCC_CSG_VERSION}

WORKDIR ${OPT_DIR}/OCC-CSG-${OCC_CSG_VERSION}/build
WORKDIR ${OPT_DIR}/OCC-CSG-${OCC_CSG_VERSION}-Release
WORKDIR ${OPT_DIR}/OCC-CSG-${OCC_CSG_VERSION}
#RUN cmake -S . -B ./build  \
#        -DCMAKE_BUILD_TYPE:STRING="Release" \
#        -DINSTALL_DIR:PATH=${OPT_DIR}/OCC-CSG-${OCC_CSG_VERSION}-Release \
#        -DOpenCASCADE_DIR=${OPT_DIR}/opencascade-${OCCT_VERSION}-Release/lib/cmake/opencascade \
#        -DCMAKE_CURRENT_SOURCE_DIR:PATH=/usr/include/freetype2/freetype \
#        -D3RDPARTY_FREETYPE_LIBRARY_DIR:PATH=/usr/lib/x86_64-linux-gnu

#WORKDIR ${OPT_DIR}/OCC-CSG-${OCC_CSG_VERSION}/build
#RUN make -j$(nproc) install
#
#WORKDIR ${OPT_DIR}
#RUN git clone https://github.com/sasobadovinac/gmsh.git gmsh_${GMSH_VERSION} && \
#    cd gmsh_${GMSH_VERSION} && \
#    git checkout tags/gmsh_${GMSH_VERSION} -b gmsh_${GMSH_VERSION}

#WORKDIR ${OPT_DIR}/gmsh_${GMSH_VERSION}/build
#WORKDIR ${OPT_DIR}/gmsh_${GMSH_VERSION}-Release
#WORKDIR ${OPT_DIR}/gmsh_${GMSH_VERSION}
#RUN cmake -S . -B ./build  \
#    -DOCC:BOOL=ON \
#    -DOCC_CAF:BOOL=ON \
#    -DCMAKE_BUILD_TYPE:STRING="Release" \
#    -DOpenCASCADE_DIR:PATH=${OPT_DIR}/opencascade-${OCCT_VERSION}-Release

WORKDIR ${OPT_DIR}
RUN git clone https://github.com/NGSolve/netgen.git netgen-v${NETEGEN_VERSION} && \
    cd netgen-v${NETEGEN_VERSION} && \
    git checkout tags/v${NETEGEN_VERSION} -b v${NETEGEN_VERSION}

WORKDIR ${OPT_DIR}/netgen-v${NETEGEN_VERSION}/build
WORKDIR ${OPT_DIR}/netgen-v${NETEGEN_VERSION}-Release
WORKDIR ${OPT_DIR}/netgen-v${NETEGEN_VERSION}

ENV LD_LIBRARY_PATH="${LD_LIBRARY_PATH}:${OPT_DIR}/opencascade-${OCCT_VERSION}-Release/lib"

RUN cmake -S . -B ${OPT_DIR}/netgen-v${NETEGEN_VERSION}/build \
    -DINSTALL_DIR=${OPT_DIR}/netgen-v${NETEGEN_VERSION}-Release \
    -DCMAKE_BUILD_TYPE:STRING="Release" \
    -DUSE_OCC:BOOL=ON \
    -DUSE_PYTHON:BOOL=ON \
    -DOpenCascade_DIR:PATH=${OPT_DIR}/opencascade-${OCCT_VERSION}-Release/lib/cmake/opencascade

WORKDIR ${OPT_DIR}/netgen-v${NETEGEN_VERSION}/build
RUN make -j$(nproc) install
