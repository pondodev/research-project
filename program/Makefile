executable_name = output

full: build run

fullclean: clean build run

build:
		g++ \
			glad.c \
			*.cpp \
			architecture_a/*.cpp \
			architecture_b/*.cpp \
			architecture_c/*.cpp \
			-lglfw \
			-lGL \
			-lX11 \
			-lpthread \
			-lXrandr \
			-lXi \
			-ldl \
			-I ./include/ \
			-o $(executable_name)

run:
		./$(executable_name)

clean:
		rm -f ./$(executable_name)