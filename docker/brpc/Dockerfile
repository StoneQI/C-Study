# for test brpc-thrift0.11.0
# brpc /brpc 目录下 构建过程中已编译为动态库
FROM ubuntu:16.04

LABEL authors="ziqi"

# support 0.9.3;0.10.0;0.11.0;0.12.0
ENV THRIFT_VERSION 0.11.0

RUN  sed -i s@/archive.ubuntu.com/@/mirrors.aliyun.com/@g /etc/apt/sources.list \
	&& sed -i s@/security.ubuntu.com/@/mirrors.aliyun.com/@g /etc/apt/sources.list \
	&& apt-get clean \
	&& apt-get update
# prepare env
RUN apt-get update && apt-get install -y --no-install-recommends \
        curl \
        apt-utils \
        openssl \
        ca-certificates

# install thrift 0.11.0
RUN buildDeps=" \
		automake \
		bison \
		curl \
		flex \
		g++ \
		libboost-dev \
		libboost-filesystem-dev \
		libboost-program-options-dev \
		libboost-system-dev \
		libboost-test-dev \
		libevent-dev \
		libssl-dev \
		libtool \
		make \
		pkg-config \
	"; \
	apt-get update && apt-get install -y --no-install-recommends $buildDeps && rm -rf /var/lib/apt/lists/* \
	&& apt-get clean -y 

# thrift 安装如下目录--headers=/usr/local/include --libs=/usr/local/lib
RUN curl -sSL "http://apache.mirrors.spacedump.net/thrift/$THRIFT_VERSION/thrift-$THRIFT_VERSION.tar.gz" -o thrift.tar.gz \
	&& mkdir -p /usr/src/thrift \
	&& tar zxf thrift.tar.gz -C /usr/src/thrift --strip-components=1 \
	&& rm thrift.tar.gz \
	&& cd /usr/src/thrift \
	&& ./bootstrap.sh \
	&& ./configure  --without-python \
	&& make \
	&& make install 
	# && cd / \
	# && rm -rf /usr/src/thrift \
	# && curl -k -sSL "https://storage.googleapis.com/golang/go1.4.linux-amd64.tar.gz" -o go.tar.gz \
	# && tar xzf go.tar.gz \
	# && rm go.tar.gz \
	# && cp go/bin/gofmt /usr/bin/gofmt \
	# && rm -rf go \
	# && apt-get purge -y --auto-remove $buildDeps


RUN apt-get update && apt-get install -y --no-install-recommends \
        git \
        g++ \
        make \
        libssl-dev \
        libgflags-dev \
        libprotobuf-dev \
        libprotoc-dev \
        protobuf-compiler \
        libleveldb-dev \
		libgoogle-perftools-dev \
        libsnappy-dev && \
        apt-get clean -y 

RUN git clone https://github.com/brpc/brpc.git brpc \
    && cd /brpc && sh config_brpc.sh --headers=/usr --libs=/usr --with-thrift \
	&& make -j "$(nproc)"

CMD [ "/bin/bash" ]
