FROM debian:buster-20201012

RUN apt-get update \
    && apt-get install -y \
        curl \
        make \
        cmake \
        unzip \
        g++

# install io-buffer library
RUN mkdir -p /tmp/io-buffer \
    && cd /tmp/io-buffer \
    && curl -LO "https://github.com/Alexander1000/io-buffer/archive/master.zip" \
    && unzip -a master.zip \
    && rm -f master.zip \
    && cd io-buffer-master \
    && cmake . \
    && make \
    && make install

# install yaml-parser library
RUN mkdir -p /tmp/yaml-parser \
    && cd /tmp/yaml-parser \
    && curl -LO "https://github.com/Alexander1000/yaml-parser/archive/master.zip" \
    && unzip -a master.zip \
    && rm -f master.zip \
    && cd yaml-parser-master \
    && cmake . \
    && make \
    && make install

# install cpp-unit-test library
RUN mkdir -p /tmp/cpp-utils \
    && cd /tmp/cpp-utils \
    && curl -LO "https://github.com/Alexander1000/cpp-unit-test/archive/master.zip" \
    && unzip -a master.zip \
    && rm -f master.zip \
    && cd cpp-unit-test-master \
    && cmake . \
    && make \
    && make install

COPY . /app

WORKDIR /app

RUN cmake . && make
