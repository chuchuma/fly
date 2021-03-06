SHELL=/bin/bash
CC=gcc
CPP=g++
CFLAGS=-O0 -fdiagnostics-color=auto -pthread -std=gnu11 -g
CXXFLAGS=$(filter-out -std=gnu11, $(CFLAGS)) -std=gnu++11 -fno-exceptions -Wno-write-strings -Wno-pointer-arith -fpermissive
MKDIRS=lib bin tst/bin .pass .pass/tst/bin .make .make/bin .make/tst/bin
PINCLUDE=$(addprefix -I,include)
EXECS=$(addprefix bin/,fly)
TESTS=$(addprefix tst/bin/,capitalC camera)
OS=$(shell uname)
ifeq ($(OS), Darwin)
GL=$(addprefix -framework ,OpenGL) $(addprefix -l, glfw3 ovr)
INCLUDE=$(PINCLUDE) $(addprefix -I,/Users/chuchu/Development/OculusSDK/LibOVR/Src)
ISED=sed -i .sed
else
GL=$(addprefix -l, GL glfw OculusVR)
INCLUDE=$(PINCLUDE) $(addprefix -I,/usr/include/ovr-0.4.4/LibOVR/Src)
ISED=sed -i
endif
LINK=$(addprefix -l, assimp GLEW SOIL) $(GL)
SRC=$(wildcard src/*.cpp)
LIBS=$(patsubst src/%.cpp, lib/%.o, $(SRC))

.PHONY: default all clean again check distcheck dist-check
.SECONDARY:
default: all
all: $(EXECS) $(TESTS)
clean:
	rm -rf $(MKDIRS)
again: clean all
check: $(addprefix .pass/,$(TESTS))

FNM=\([a-z_A-Z]*\)
.make/%.d: %.c
	@mkdir -p $(@D)
	@$(CC) -MM $(CCSTD) $(INCLUDE) $< -o $@
.make/%.d: %.cpp
	@mkdir -p $(@D)
	$(CPP) -MM $(CXXSTD) $(INCLUDE) $< -o $@
.make/lib/%.o.d: .make/src/%.d | .make/lib
	@sed 's/$(FNM)\.o/lib\/\1.o/g' $< > $@
.make/bin/%.d: .make/%.d | .make/bin
	@sed 's/include\/$(FNM).h/lib\/\1.o/g' $< > $@
	@$(ISED) 's/$(FNM).o:/bin\/\1:/g' $@
	@perl make/depend.pl $@ > $@.bak
	@mv $@.bak $@
.make/tst/bin/%.d: .make/tst/%.d | .make/tst/bin
	@sed 's/include\/$(FNM).h/lib\/\1.o/g' $< > $@
	@$(ISED) 's/$(FNM).o:/tst\/bin\/\1:/g' $@
	@perl make/depend.pl $@ > $@.bak
	@mv $@.bak $@
MAKES=$(addsuffix .d,$(addprefix .make/, $(EXECS) $(TESTS) $(LIBS)))
-include $(MAKES)
distcheck dist-check:
	@rm -rf .pass
	@make --no-print-directory check
.pass/tst/bin/%: tst/bin/% | .pass/tst/bin
	@printf "$<: "
	@$<\
		&& echo -e "\033[0;32mpass\033[0m" && touch $@\
		|| echo -e "\033[0;31mfail\033[0m"
$(MKDIRS):
	@mkdir -p $@
$(EXECS): | bin
bin/%: %.cpp
	$(CPP) $(CXXFLAGS) $(INCLUDE) $^ -o $@ $(LINK)
bin/%: %.c
	$(CC) $(CFLAGS) $(INCLUDE) $^ -o $@ $(LINK)
lib/%.o: src/%.cpp include/%.h | lib
	$(CPP) -c $(CXXFLAGS) $(INCLUDE) $< -o $@
lib/%.o: src/%.c include/%.h | lib
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@
tst/bin/%: tst/%.cpp | tst/bin
	$(CPP) $(CXXFLAGS) $(INCLUDE) $^ -o $@
tst/bin/%: tst/%.c | tst/bin
	$(CC) $(CFLAGS) $(INCLUDE) $^ -o $@
