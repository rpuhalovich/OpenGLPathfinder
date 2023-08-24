run: build
	./build/OpenGLPathfinder

build: project
	cmake --build build

project:
	rm -f compile_commands.json
	cmake -S . -B build
	cp build/compile_commands.json compile_commands.json

clean:
	rm -rf build compile_commands.json

.SILENT:
