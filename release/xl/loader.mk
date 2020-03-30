
#///////////// OPTIONS ////////////////
option = -nologo /Ixl/loader /Iinclude -c /DCLNOCODE /DCLPC /GX /Zi
.SUFFIXES : .exe .obj .cpp


#///////////// TARGET ////////////////
TARGET = loader.dll


#///////////// VARS ////////////////
ROOT = xl/loader
OBJ = objs
Z = bin/public/ntv
CC = cl
FILES = $(OBJ)/loader.obj $(OBJ)/loader_frontal.obj


#///////////// RULE ////////////////
{$(ROOT)}.cpp{$(OBJ)}.obj:
     $(CC) $(option) /Fo$(OBJ)/$(<B).obj /Tp $(ROOT)/$(<B).cpp

{csrc}.cpp{$(OBJ)}.obj:
     $(CC) $(option) /Fo$(OBJ)/$(<B).obj /Tp $(ROOT)/$(<B).cpp

#///////////// ALL ////////////////
all: $(TARGET)

#///////////// LINK ////////////////
$(TARGET): $(FILES)
     lib /NOLOGO /def $(FILES) /out:loader.lib
	 lib /NOLOGO $(FILES) /out:loader.lib
	 move loader.lib lib/ntv
	 move loader.exp lib/ntv
	 

