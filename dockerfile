FROM ubuntu:latest
RUN apt-get update
RUN apt-get install -y --no-install-recommends apt-utils build-essential htop sudo git g++
RUN useradd -m docker && echo "docker:docker" | chpasswd && adduser docker sudo
RUN cd / && mkdir tp2
USER docker