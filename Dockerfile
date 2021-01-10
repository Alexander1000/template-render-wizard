FROM debian:buster-20201012

RUN echo 'deb http://deb.debian.org/debian testing main' >> /etc/apt/sources.list \
    && apt-get update -y \
    && apt-get install -y \
        gcc \
        g++ \
        curl \
        make \
        cmake \
        unzip \
        build-essential

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

# install syntax-tree library
RUN mkdir -p /tmp/syntax-tree \
    && cd /tmp/syntax-tree \
    && curl -LO "https://github.com/Alexander1000/syntax-tree/archive/master.zip" \
    && unzip -a master.zip \
    && rm -f master.zip \
    && cd syntax-tree-master \
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

COPY . /app

WORKDIR /app

RUN cmake . && make
