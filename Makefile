run: build
	./build/OpenGLPathfinder

build: project
	cmake --build build

project:
	rm -f compile_commands.json
	cp build/compile_commands.json compile_commands.json
	cmake -S . -B build

clean:
	rm -rf build compile_commands.json

.SILENT:
