inner:
	g++ src/map.cpp src/polygon.cpp src/line.cpp src/canvas.cpp src/bezier.cpp src/point.cpp src/matrix.cpp -o bin/inner

ui:
	g++ src/ui.cpp src/polygon.cpp src/canvas.cpp src/point.cpp src/matrix.cpp src/line.cpp src/font.cpp src/view.cpp src/map.cpp src/bezier.cpp src/fill.cpp -o bin/ui -lncurses
