run: build
	./build/OpenGLPathfinder

build: project
	cmake --build build

project:
	cmake -S . -B build

clean:
	rm -rf build

.SILENT:
