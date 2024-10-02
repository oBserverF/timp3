FROM ubuntu:18.04      
RUN apt-get update
RUN apt install qt5-default -y --fix-missing
RUN apt install g++ -y --fix-missing
RUN apt install build-essential -y --fix-missing
RUN apt install sqlite3 libsqlite3-dev -y --fix-missing
RUN mkdir -p /home/root/server/
COPY . /home/root/server
WORKDIR /home/root/server
RUN qmake timp3.pro
RUN make
CMD ["./timp3"]