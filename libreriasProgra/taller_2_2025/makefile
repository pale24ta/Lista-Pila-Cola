# Define el compilador
CXX = g++

# Define las opciones de compilación (flags)
# -Wall: Habilita todas las advertencias (¡muy recomendado!)
# -g: Incluye información de depuración para gdb
CXXFLAGS = -Wall -g

# Define el directorio de los encabezados personalizados (tus .hpp)
LIBRERIAS_DIR = ../librerias

# Define el nombre del ejecutable
TARGET = lpc.out

# Define los archivos fuente (.cpp) que se compilarán
# En tu caso, solo es main.cpp
SRCS = main.cpp

# Genera automáticamente la lista de archivos objeto (.o) a partir de los fuentes (.cpp)
OBJS = $(SRCS:.cpp=.o)

# Regla por defecto: compilar el ejecutable
all: $(TARGET)

# Regla para construir el ejecutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) 

# Regla para compilar archivos .cpp en .o
# -I$(LIBRERIAS_DIR): Indica al compilador dónde buscar los archivos de encabezado (.hpp)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -I$(LIBRERIAS_DIR) -o $@ 

# Regla para limpiar los archivos generados
clean:
	rm -f $(OBJS) $(TARGET) 

# Marca 'all' y 'clean' como objetivos "ficticios" (no son archivos reales)
.PHONY: all clean
