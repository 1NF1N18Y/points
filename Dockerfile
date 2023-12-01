FROM amd64/ubuntu:18.04 AS base

EXPOSE 3466/tcp
EXPOSE 3465/tcp

ENV DEBIAN_FRONTEND=noninteractive

#Add ppa:bitcoin/bitcoin repository so we can install libdb4.8 libdb4.8++
RUN apt-get update && \
	apt-get install -y software-properties-common && \
	add-apt-repository ppa:bitcoin/bitcoin

#Install runtime dependencies
RUN apt-get update && \
	apt-get install -y --no-install-recommends \
	bash net-tools libminiupnpc10 \
	libevent-2.1 libevent-pthreads-2.1 \
	libdb4.8 libdb4.8++ \
	libboost-system1.65 libboost-filesystem1.65 libboost-chrono1.65 \
	libboost-program-options1.65 libboost-thread1.65 \
	libzmq5 && \
	apt-get clean

FROM base AS build

#Install build dependencies
RUN apt-get update && \
	apt-get install -y --no-install-recommends \
	bash net-tools build-essential libtool autotools-dev automake git \
	pkg-config libssl-dev libevent-dev bsdmainutils python3 \
	libboost-system1.65-dev libboost-filesystem1.65-dev libboost-chrono1.65-dev \
	libboost-program-options1.65-dev libboost-test1.65-dev libboost-thread1.65-dev \
	libzmq3-dev libminiupnpc-dev libdb4.8-dev libdb4.8++-dev && \
	apt-get clean


#Build Points from source
COPY . /home/points/build/Points/
WORKDIR /home/points/build/Points
RUN ./autogen.sh && ./configure --disable-tests --with-gui=no && make

FROM base AS final

#Add our service account user
RUN useradd -ms /bin/bash points && \
	mkdir /var/lib/points && \
	chown points:points /var/lib/points && \
	ln -s /var/lib/points /home/points/.points && \
	chown -h points:points /home/points/.points

VOLUME /var/lib/points

#Copy the compiled binaries from the build
COPY --from=build /home/points/build/Points/src/pointsd /usr/local/bin/pointsd
COPY --from=build /home/points/build/Points/src/points-cli /usr/local/bin/points-cli

WORKDIR /home/points
USER points

CMD /usr/local/bin/pointsd -datadir=/var/lib/points -printtoconsole -onlynet=ipv4
