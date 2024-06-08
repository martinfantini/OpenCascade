
FROM emscripten_opencascade_base:latest

ENV OPT_DIR /opt
ENV THIRDPARTY_DIR ${OPT_DIR}/3rdparty
ENV OCCT_VERSION 7_7_2
ENV FREETYPE_VERSION 2-13-2

COPY CMakeLists.txt ${OPT_DIR}/opencascade-${OCCT_VERSION}/samples/webgl

WORKDIR ${OPT_DIR}/web-gl-release

RUN cd ${OPT_DIR}/opencascade-${OCCT_VERSION}/samples/webgl && \
    emcmake cmake -S . -B Build  \
        -DCMAKE_INSTALL_PREFIX:PATH=${OPT_DIR}/web-gl-release \
        -Dfreetype_DIR=${THIRDPARTY_DIR}/freetype-${FREETYPE_VERSION}-wasm/lib/cmake/freetype \
        -DOpenCASCADE_DIR=${OPT_DIR}/opencascade-${OCCT_VERSION}-wasm/lib/cmake/opencascade \
        -DCMAKE_BUILD_TYPE:STRING="Release" \
        -DBUILD_LIBRARY_TYPE="Static" 

RUN cd ${OPT_DIR}/opencascade-${OCCT_VERSION}/samples/webgl/Build && emmake make -j$(nproc) install

RUN mkdir -p ${OPT_DIR}/opencascade-${OCCT_VERSION}/samples/webgl/Build/samples && \
    cp ${OPT_DIR}/opencascade-${OCCT_VERSION}/data/occ/Ball.brep ${OPT_DIR}/opencascade-${OCCT_VERSION}/samples/webgl/Build/samples

RUN cd ${OPT_DIR}/opencascade-${OCCT_VERSION}/samples/webgl/Build && \
    cp ${OPT_DIR}/opencascade-${OCCT_VERSION}/data/occ/Ball.brep ${OPT_DIR}/opencascade-${OCCT_VERSION}/samples/webgl/Build/samples

RUN cp ${OPT_DIR}/opencascade-${OCCT_VERSION}/dox/resources/occ_logo.png ${OPT_DIR}/opencascade-${OCCT_VERSION}/samples/webgl/Build/OCC_logo.png
RUN cp ${OPT_DIR}/opencascade-${OCCT_VERSION}/samples/webgl/occt-webgl-sample.html ${OPT_DIR}/opencascade-${OCCT_VERSION}/samples/webgl/Build/occt-webgl-sample.html

WORKDIR ${OPT_DIR}/opencascade-${OCCT_VERSION}/samples/webgl/Build

CMD python3 -m http.server 7000

EXPOSE 7000
