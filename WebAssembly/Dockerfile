# download the data from the last emscripten
FROM emscripten/emsdk:3.1.61

ENV OPT_DIR /opt
ENV THIRDPARTY_DIR ${OPT_DIR}/3rdparty
ENV RAPIJSON_VERSION master
ENV FREETYPE_VERSION 2-13-2
ENV DARCO_VERSION 1.5.7
ENV OCCT_VERSION 7_7_2
ENV DOCTEST_VERSION 2.4.11
ENV GMSH_VERSION 4_4_0
ENV NETEGEN_VERSION 6.2.2403
ENV TK_VERSION 8-6-b3

RUN apt-get clean && apt-get update

RUN apt-get -y install build-essential git wget vim cmake automake libtool autoconf p7zip-full p7zip-rar python3 python3-dev libpthread-stubs0-dev libx11-dev cmake-curses-gui 

# Build RapidJson
WORKDIR $THIRDPARTY_DIR
#RUN git clone https://github.com/Tencent/rapidjson.git rapidjson-${RAPIJSON_VERSION} && \
#    cd rapidjson-${RAPIJSON_VERSION} && \
#    git checkout tags/v${RAPIJSON_VERSION} -b v${RAPIJSON_VERSION}
RUN git clone https://github.com/Tencent/rapidjson.git rapidjson-${RAPIJSON_VERSION}

# Build Freetype
WORKDIR $THIRDPARTY_DIR
RUN git clone https://github.com/freetype/freetype.git freetype-${FREETYPE_VERSION} && \
    cd freetype-${FREETYPE_VERSION} && \
    git checkout tags/VER-${FREETYPE_VERSION} -b VER-${FREETYPE_VERSION}

WORKDIR $THIRDPARTY_DIR/freetype-${FREETYPE_VERSION}
RUN sh autogen.sh && mkdir build
RUN emcmake cmake -S . -B ./build -DCMAKE_INSTALL_PREFIX=$THIRDPARTY_DIR/freetype-${FREETYPE_VERSION}-wasm

WORKDIR $THIRDPARTY_DIR/freetype-${FREETYPE_VERSION}-wasm

WORKDIR $THIRDPARTY_DIR/freetype-${FREETYPE_VERSION}/build
RUN emmake make -j$(nproc) install

WORKDIR $THIRDPARTY_DIR
RUN git clone https://github.com/google/draco.git draco-${DARCO_VERSION} && \
    cd draco-${DARCO_VERSION} && \
    git checkout tags/${DARCO_VERSION} -b ${DARCO_VERSION}

WORKDIR $THIRDPARTY_DIR/draco-${DARCO_VERSION}/build
WORKDIR $THIRDPARTY_DIR/draco-${DARCO_VERSION}-wasm
WORKDIR $THIRDPARTY_DIR/draco-${DARCO_VERSION}

ENV EMSCRIPTEN /emsdk/upstream/emscripten
RUN emcmake cmake -S . -B ./build -DCMAKE_INSTALL_PREFIX=$THIRDPARTY_DIR/draco-${DARCO_VERSION}-wasm -DCMAKE_BUILD_TYPE:STRING="Release" -DDRACO_WASM:BOOL=ON -DBUILD_LIBRARY_TYPE:STRING="Static" -DDRACO_JS_GLUE:BOOL=OFF

WORKDIR $THIRDPARTY_DIR/draco-${DARCO_VERSION}/build
RUN emmake make -j$(nproc) install

WORKDIR $THIRDPARTY_DIR
RUN git clone https://github.com/gkv311/tcl.git tcl
WORKDIR $THIRDPARTY_DIR/tcl
RUN /bin/bash occ_tcl_build_wasm.sh

WORKDIR ${OPT_DIR}
RUN git clone https://github.com/Open-Cascade-SAS/OCCT.git opencascade-${OCCT_VERSION} && \
    cd opencascade-${OCCT_VERSION} && \
    git checkout tags/V${OCCT_VERSION} -b V${OCCT_VERSION}

WORKDIR ${OPT_DIR}/opencascade-${OCCT_VERSION}/build
WORKDIR ${OPT_DIR}/opencascade-${OCCT_VERSION}
RUN emcmake cmake -S . -B ${OPT_DIR}/opencascade-${OCCT_VERSION}/build \
    -DINSTALL_DIR=${OPT_DIR}/opencascade-${OCCT_VERSION}-wasm \
    -DBUILD_MODULE_Draw:BOOL=OFF \
    -DBUILD_MODULE_DETools:BOOL=OFF \
    -DBUILD_LIBRARY_TYPE="Static" \
    -DBUILD_DOC_Overview:BOOL=FALSE \
    -DCMAKE_BUILD_TYPE:STRING="Release" \
    -DUSE_FREETYPE:BOOL=ON \
    -D3RDPARTY_FREETYPE_DIR:PATH=$THIRDPARTY_DIR/freetype-${FREETYPE_VERSION}-wasm \
    -D3RDPARTY_FREETYPE_INCLUDE_DIR_freetype2=$THIRDPARTY_DIR/freetype-${FREETYPE_VERSION}-wasm/include \
    -D3RDPARTY_FREETYPE_INCLUDE_DIR_ft2build=$THIRDPARTY_DIR/freetype-${FREETYPE_VERSION}-wasm/include/freetype2 \
    -D3RDPARTY_FREETYPE_LIBRARY_DIR=$THIRDPARTY_DIR/freetype-2.7.1-wasm/lib \
    -DUSE_RAPIDJSON:BOOL=ON \
    -D3RDPARTY_RAPIDJSON_DIR:PATH=$THIRDPARTY_DIR/rapidjson-${RAPIJSON_VERSION} \
    -D3RDPARTY_RAPIDJSON_INCLUDE_DIR:PATH=$THIRDPARTY_DIR/rapidjson-${RAPIJSON_VERSION}/include \
    -DUSE_DRACO:BOOL=ON \
    -D3RDPARTY_DRACO_DIR:PATH=$THIRDPARTY_DIR/draco-${DARCO_VERSION}-wasm \
    -D3RDPARTY_DRACO_INCLUDE_DIR:FILEPATH=$THIRDPARTY_DIR/draco-${DARCO_VERSION}-wasm/include \
    -D3RDPARTY_DRACO_LIBRARY_DIR:PATH=$THIRDPARTY_DIR/draco-${DARCO_VERSION}-wasm/lib \
    -DUSE_TK:BOOL=OFF \
    -D3RDPARTY_TCL_DIR:PATH=$THIRDPARTY_DIR/tcl/install/tcl-wasm32 \
    -D3RDPARTY_TCL_INCLUDE_DIR:PATH=$THIRDPARTY_DIR/tcl/install/tcl-wasm32/include \
    -D3RDPARTY_TCL_LIBRARY_DIR:PATH=$THIRDPARTY_DIR/tcl/install/tcl-wasm32/lib \
    -D3RDPARTY_TCL_LIBRARY:FILEPATH=$THIRDPARTY_DIR/tcl/install/tcl-wasm32/lib/libtcl8.6.a \
    -DUSE_GLES2:BOOL=OFF \
    -DFREETYPE_LIBRARY:PATH=$THIRDPARTY_DIR/freetype-${FREETYPE_VERSION}-wasm/lib \
    -DFREETYPE_INCLUDE_DIRS:PATH=$THIRDPARTY_DIR/freetype-${FREETYPE_VERSION}-wasm/include/freetype2 \
    -DLDFLAGS:STRING="-pthread"

WORKDIR ${OPT_DIR}/opencascade-${OCCT_VERSION}/build
RUN emmake make -j$(nproc) install

WORKDIR ${OPT_DIR}
RUN git clone https://github.com/doctest/doctest.git doctest-v${DOCTEST_VERSION} && \
    cd doctest-v${DOCTEST_VERSION} && \
    git checkout tags/v${DOCTEST_VERSION} -b v${DOCTEST_VERSION}

#WORKDIR ${OPT_DIR}/gmsh
#RUN git clone https://github.com/sasobadovinac/gmsh.git gmsh-v${GMSH_VERSION} && \
#    cd gmsh-v${GMSH_VERSION} && \
#    git checkout tags/gmsh_${GMSH_VERSION} -b gmsh_${GMSH_VERSION}

WORKDIR ${OPT_DIR}
RUN git clone https://github.com/tcltk/tk.git tk-v${TK_VERSION} && \
    cd tk-v${TK_VERSION} && \
    git checkout tags/core-${TK_VERSION} -b core-${TK_VERSION}

#WORKDIR tk-v${TK_VERSION}/unix
#RUN emconfigure ./configure --with-tcl=$THIRDPARTY_DIR/tcl/install/tcl-wasm32/lib
#RUN emmake make -j$(nproc) install

WORKDIR ${OPT_DIR}
RUN git clone https://github.com/NGSolve/netgen.git netgen-v${NETEGEN_VERSION} && \
    cd netgen-v${NETEGEN_VERSION} && \
    git checkout tags/v${NETEGEN_VERSION} -b v${NETEGEN_VERSION}

#WORKDIR ${OPT_DIR}/netgen-v${NETEGEN_VERSION}/build
#WORKDIR ${OPT_DIR}/netgen-v${NETEGEN_VERSION}-wasm
#WORKDIR ${OPT_DIR}/netgen-v${NETEGEN_VERSION}
#
#RUN emcmake cmake -S . -B ${OPT_DIR}/netgen-v${NETEGEN_VERSION}/build \
#        -DCMAKE_INSTALL_PREFIX=${OPT_DIR}/netgen-v${NETEGEN_VERSION}-wasm \
#        -DBUILD_LIBRARY_TYPE="Static" \
#        -DCMAKE_BUILD_TYPE:STRING="Release" \
#        -DUSE_PYTHON:BOOL=OFF \
#        -DUSE_OCC:BOOL=ON \
#        -DBUILD_OCC:BOOL=OFF \
#        -DOpenCascade_DIR:PATH=${OPT_DIR}/opencascade-${OCCT_VERSION}-wasm/lib/cmake/opencascade/  \
#        -DTCL_INCLUDE_PATH:PATH=${OPT_DIR}/3rdparty/tcl/install/tcl-wasm32/include/  \
#        -DTCL_LIBRARY:PATH=${OPT_DIR}/3rdparty/tcl/install/tcl-wasm32/lib/ \
#        -DTCL_TCLSH:PATH=${OPT_DIR}/3rdparty/tcl/install/tcl-wasm32/lib/  \
#        -DZLIB_LIBRARY:PATH=/usr/lib/x86_64-linux-gnu \
#        -DZLIB_INCLUDE_DIR=/usr/include

#WORKDIR ${OPT_DIR}/netgen-v${NETEGEN_VERSION}/build
#RUN emmake make -j$(nproc) install
