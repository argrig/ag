VPATH := prog
lib_files = $(wildcard my*.cpp)
prg_files = $(wildcard prog/*.cpp)
src_files = $(lib_files) $(prg_files) 
obj_files = $(patsubst %.cpp, %.o, $(lib_files))
progs = $(patsubst %.cpp, %.run, $(prg_files))

# OPT = -O0 -g -pipe -w 
OPT = -w

all: libmy.a $(progs)
#all:
#	@echo $(progs)

libmy.a: $(obj_files)
	ar rcv $@ $^

%.o: %.cpp
	@ echo compiling object file $@ ...
	g++ $(OPT) -c $?

%.cpp: %.h
	touch $@

clean:
	@ echo removing object files: $(obj_files) ... && \
		rm -f $(obj_files) 
	@ echo removing compiled programs: $(progs) ... && \
		rm -f $(progs) 
	@ echo removing backup files: *.~ ... && \
		find . -iname \*\~ -exec rm -f {} \; && \
		echo 'done'

%.run: libmy.a %.cpp
	g++ $(OPT) -I.. -I. -o $@ $(patsubst %.run, %.cpp, $@) -L. -L.. -lmy -lgmpxx -lgmp 
