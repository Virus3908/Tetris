#!/bin/bash
docker rmi -f linux
docker build -t linux -f Docker/Dockerfile .
docker run --name lin -p 8000:8000 --rm -it linux 
