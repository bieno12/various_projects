start_a: clean a.exe

a.exe: main.cpp consoleAPI.cpp editor.cpp
	g++  $^  -o a.exe

clean:
	rm --force a.exe
.PHONY: start_a clean