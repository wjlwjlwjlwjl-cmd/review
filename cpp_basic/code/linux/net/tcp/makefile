all: server client
server: TcpServer.cc
	g++ $^ -o $@ -lfmt -lspdlog -g
client: TcpClient.cc
	g++ $^ -o $@ -lfmt -lspdlog -lgflags -g

.PHONY:clean
clean:
	rm -rf server
