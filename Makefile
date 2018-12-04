# ----------------------------------------------------------------------------
# Makefile.linux
#
# release: 0.1 (24-Jun-2018) create makefile
#
# purpose: searches recursively in current directory for cpp files,
#          compile each source file and link them in a linux executable.
# ----------------------------------------------------------------------------

CC = g++
APP = game

MAIN = ./game-prototype/main.cpp
SRCDIR  = ./game-prototype/src
SRCEXT  = cpp
OBJDIR  = bin/.temp
BUILDDIR = bin/Linux
RESOURCES = game-prototype/assets

OPTIMIZATION_LEVELS = -O2 -D _DEBUG
INCLUDES =
SDL2_FLAGS = `sdl2-config --cflags --libs` -lSDL2 -lSDL2_mixer -lSDL2_ttf -lSDL2_image
GLFLAGS = -I /usr/include -lGL -lGLEW
CFLAGS  = -Wall -std=c++11 $(GLFLAGS) $(SDL2_FLAGS) $(INCLUDES) $(OPTIMIZATION_LEVELS)
OFLAGS  = -Wall -std=c++11 $(GLFLAGS) $(SDL2_FLAGS) $(INCLUDES)

RM = rm -rf
MOVE = mv
COPY = cp
MAKEDIR = mkdir -p

# ----------------------------------------------------------------------------

SRCS    := $(shell find $(SRCDIR) -name '*.$(SRCEXT)')
SRCDIRS := $(shell find . -name '*.$(SRCEXT)' -exec dirname {} \; | uniq)
OBJS    := $(patsubst %.$(SRCEXT),$(OBJDIR)/%.o,$(SRCS))

all : $(APP)
$(APP): buildrepo resources $(OBJS)
	@echo "";
	@echo "Linking...";
	@echo "$(CC) $(OBJS) $(OFLAGS) $(MAIN) -o $@"
	@$(CC) $(OBJS) $(OFLAGS) $(MAIN) -o $@
	${MOVE} $(APP) bin/$(APP)

$(OBJDIR)/%.o: %.$(SRCEXT)
	@echo "";
	@echo "Compiling...";
	@echo "$(CC) $(CFLAGS) $< -o $@";
	@$(CC) $(CFLAGS) -c $< -o $@

resources:
	@echo "";
	@echo "Copying resources...";
	${COPY} -r $(RESOURCES) ./bin/assets

clean:
	@echo "";
	@echo "Cleaning...";
	${MAKEDIR} ${BUILDDIR}
	${MOVE} ${APP} ${BUILDDIR}/${APP}
	$(MOVE) ./assets ${BUILDDIR}/assets
	$(RM) -r $(OBJDIR)

buildrepo:
	@echo "";
	@echo "Creating build dir...";
	$(RM) bin
	${MAKEDIR} bin
	$(call make-repo)

define make-repo
	for dir in `find $(SRCDIR) -type d`; \
	do \
		$(MAKEDIR) $(OBJDIR)/$$dir; \
	done
endef
