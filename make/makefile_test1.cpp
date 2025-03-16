


CC = g++
CFLAGS = -c -Wall  -g  -I/usr/local/include/hiredis/ 
SRC := redis_stub.cpp redis_async_subs.cpp redis_ayn.cpp
# := (常量) 使用 $(变量名替换)
objects := $(SRC:%.cpp=%.o)
LDFLAGS = -L/usr/local/lib   -lpthread -lhiredis -levent

all: $(objects)
	$(CC) -g -o tant $(objects)  $(LDFLAGS)

$(objects): %.o: %.cpp
	$(CC) $(CFLAGS) $< -g -o $@
clean:
	echo $(objects)
	echo $(CFLAGS)
	rm *.o tant -rf

