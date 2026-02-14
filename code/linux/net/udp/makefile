all: server client
server: udpServer.cc
	g++ $^ -o $@ -l spdlog -lfmt
client: udpClient.cc
	g++ $^ -o $@ -l gflags -lspdlog -lfmt
.PHONY:clean
clean:
	rm -rf server client
