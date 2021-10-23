executable_name = output

full: build run

fullclean: clean build run

build:
		g++ \
			--std=c++17 \
			glad.c \
			*.cpp \
			architecture_a/*.cpp \
			architecture_b/*.cpp \
			architecture_c/*.cpp \
			architecture_d/*.cpp \
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

test:
		g++ \
			--std=c++17 \
			glad.c \
			*.cpp \
			architecture_a/*.cpp \
			architecture_b/*.cpp \
			architecture_c/*.cpp \
			architecture_d/*.cpp \
			-lglfw \
			-lGL \
			-lX11 \
			-lpthread \
			-lXrandr \
			-lXi \
			-ldl \
			-I ./include/ \
			-O0 \
			-o $(executable_name)
		./$(executable_name) > o0.output

		g++ \
			--std=c++17 \
			glad.c \
			*.cpp \
			architecture_a/*.cpp \
			architecture_b/*.cpp \
			architecture_c/*.cpp \
			architecture_d/*.cpp \
			-lglfw \
			-lGL \
			-lX11 \
			-lpthread \
			-lXrandr \
			-lXi \
			-ldl \
			-I ./include/ \
			-O1 \
			-o $(executable_name)
		./$(executable_name) > o1.output

		g++ \
			--std=c++17 \
			glad.c \
			*.cpp \
			architecture_a/*.cpp \
			architecture_b/*.cpp \
			architecture_c/*.cpp \
			architecture_d/*.cpp \
			-lglfw \
			-lGL \
			-lX11 \
			-lpthread \
			-lXrandr \
			-lXi \
			-ldl \
			-I ./include/ \
			-O2 \
			-o $(executable_name)
		./$(executable_name) > o2.output

		g++ \
			--std=c++17 \
			glad.c \
			*.cpp \
			architecture_a/*.cpp \
			architecture_b/*.cpp \
			architecture_c/*.cpp \
			architecture_d/*.cpp \
			-lglfw \
			-lGL \
			-lX11 \
			-lpthread \
			-lXrandr \
			-lXi \
			-ldl \
			-I ./include/ \
			-O3 \
			-o $(executable_name)
		./$(executable_name) > o3.output
