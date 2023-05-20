#-----------------------------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License. See LICENSE in the project root for license information.
#-----------------------------------------------------------------------------------------

FROM python:3.10-slim-buster

# Install pylint
RUN pip install pylint numpy flake8

# Configure apt
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update \
    && apt-get -y install --no-install-recommends apt-utils 2>&1 \
    && apt-get -y upgrade

# Install git, process tools, lsb-release (common in install instructions for CLIs)
RUN apt-get -y install git procps lsb-release wget

# Install any missing dependencies for enhanced language service
RUN apt-get install -y libicu[0-9][0-9]

# Install devtools for opencv
RUN apt-get install -y build-essential cmake unzip pkg-config manpages-dev gdb g++\
    # Install opencv image tools
    && apt-get install -y libjpeg-dev libpng-dev libtiff-dev libavcodec-dev libavformat-dev libswscale-dev libv4l-dev libxvidcore-dev libx264-dev libatlas-base-dev gfortran python3-dev libgtk-3-dev libavcodec-dev libavformat-dev libswscale-dev libv4l-dev libxvidcore-dev libx264-dev libjpeg-dev libpng-dev libtiff-dev gfortran openexr libatlas-base-dev libtbb2 libtbb-dev libdc1394-22-dev libopenexr-dev libgstreamer-plugins-base1.0-dev libgstreamer1.0-dev

# Install OpenCV by compiling it.
WORKDIR /opencv
RUN wget -O opencv.zip https://github.com/opencv/opencv/archive/4.7.0.zip \
    && wget -O opencv_contrib.zip https://github.com/opencv/opencv_contrib/archive/4.7.0.zip \
    && unzip opencv.zip \
    && unzip opencv_contrib.zip \
    && mv opencv-4.7.0 opencv \
    && mv opencv_contrib-4.7.0 opencv_contrib
RUN mkdir /opencv/opencv/build
WORKDIR /opencv/opencv/build
# Change the last line to be the number of cores you allocate to docker - j4 for 4 cores
RUN cmake -D CMAKE_BUILD_TYPE=RELEASE \
	-D CMAKE_INSTALL_PREFIX=/usr/local \
	-D INSTALL_PYTHON_EXAMPLES=ON \
	-D INSTALL_C_EXAMPLES=ON \
	-D OPENCV_ENABLE_NONFREE=ON \
    -D OPENCV_GENERATE_PKGCONFIG=ON \
	-D OPENCV_EXTRA_MODULES_PATH=/opencv/opencv_contrib/modules \
	-D PYTHON_EXECUTABLE=/usr/local/bin/python \
	-D BUILD_EXAMPLES=ON .. \
    && make -j$(nproc) && make install && ldconfig



RUN mkdir /workspace
WORKDIR /workspace

# Install Python dependencies from requirements.txt if it exists
COPY requirements.txt /workspace/
RUN if [ -f "requirements.txt" ]; then pip install -r requirements.txt; fi

# Clean up
RUN apt-get autoremove -y \
    && apt-get clean -y \
    && rm -rf /var/lib/apt/lists/*
ENV DEBIAN_FRONTEND=dialog

# Set the default shell to bash rather than sh
ENV SHELL /bin/bash