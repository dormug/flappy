# Usage:
# make        # compile all binary
# make run    # run executable
# make clean  # remove ALL binaries and objects

EXECUTABLE_NAME = flappy

SRC = src
BIN = bin
OBJ = $(BIN)/obj
RES = res

sdl        = -framework SDL2
sdl_image  = -framework SDL2_image 

CC = gcc
CFLAGS = -c -I include/ -MMD
LDFLAGS = ${sdl} ${sdl_image} -F/Library/Frameworks

EXE_SPECIFIC = main.c

EM = emcc
EMFLAGS = -c -I include/ -MMD
EMLFLAGS = -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --preload-file $(RES)

WEB = $(BIN)/web
WEB_OBJ = $(WEB)/obj
WEB_SRC = web

EXECUTABLE_FILES = $(EXECUTABLE_NAME:%=$(BIN)/%)
SOURCE_FILES     = $(patsubst ${SRC}/%, %, $(wildcard ${SRC}/*.c))
OBJECT_FILES     = $(SOURCE_FILES:%.c=$(OBJ)/%.o)
DEPENDENCY_FILES = $(SOURCE_FILES:%.c=$(OBJ)/%.d)

# web
WEB_EXECUTABLE          = $(WEB)/$(EXECUTABLE_NAME).js

WEB_SOURCE_FILES        = $(filter-out $(EXE_SPECIFIC), $(SOURCE_FILES))
WEB_OBJECT_FILES        = $(WEB_SOURCE_FILES:%.c=$(WEB_OBJ)/%.o)

WEB_SPECIFIC_FILES      = $(patsubst $(WEB_SRC)/%, %, $(wildcard $(WEB_SRC)/*.c))
WEB_SPECIFIC_OBJ        = $(WEB_SPECIFIC_FILES:%.c=$(WEB_OBJ)/%.o)
WEB_INDEX               = bin/web/index.html
WEB_INDEX_SOURCE        = web/index.html

GREEN = \033[0;32m
NC = \033[0m # No Color

build: $(EXECUTABLE_FILES)

-include ${DEPENDENCY_FILES}

run: $(EXECUTABLE_FILES)
	@echo "\n${GREEN}Running...${NC}"
	./bin/${EXECUTABLE_NAME}

clean:
	@echo "${GREEN}Cleaning up...${NC}"
	rm -rf $(BIN)

web: $(WEB_INDEX) $(WEB_EXECUTABLE)

runweb: $(WEB_INDEX) $(WEB_EXECUTABLE)
	@echo "${GREEN}Running...${NC}"
	emrun $(WEB)/index.html --browser chrome

.PHONY: build run clean web runweb

$(EXECUTABLE_FILES): $(OBJECT_FILES)
	@echo "\n${GREEN}Linking ${@F}${NC}"
	$(CC) $(LDFLAGS) -o $@ $^
	@echo "\n${GREEN}Build successful!${NC}"

$(OBJECT_FILES): $(OBJ)/%.o: $(SRC)/%.c
	@echo "${GREEN}Compiling $<${NC}"
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $<

##############################################

$(WEB_EXECUTABLE): $(WEB_OBJECT_FILES) $(WEB_SPECIFIC_OBJ)
	@echo "\n${GREEN}Linking ${@F}${NC}"
	$(EM) $(EMLFLAGS) -o $@ $^
	@echo "\n${GREEN}Build successful!${NC}"

$(WEB_OBJECT_FILES): $(WEB_OBJ)/%.o: $(SRC)/%.c
	@echo "${GREEN}Compiling $<${NC}"
	@mkdir -p $(@D)
	$(EM) $(EMFLAGS) -o $@ $<

$(WEB_SPECIFIC_OBJ): $(WEB_OBJ)/%.o: $(WEB_SRC)/%.c
	@echo "${GREEN}Compiling $<${NC}"
	@mkdir -p $(@D)
	$(EM) $(EMFLAGS) -o $@ $<

$(WEB_INDEX): $(WEB_INDEX_SOURCE)
	@echo "${GREEN}Copying index.html...${NC}\n"
	@mkdir -p $(@D)
	@cp $(WEB_INDEX_SOURCE) $(WEB_INDEX)
