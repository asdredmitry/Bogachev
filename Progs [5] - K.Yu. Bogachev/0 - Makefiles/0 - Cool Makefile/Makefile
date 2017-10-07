#############################################################################
# Это makefile для проектов, умещающихся в один каталог

# Стандартные опции:

    TargetName		:=App		# имя исполняемого файла
    Debug		:=y		# отладка - y, оптимизация - n
    CompilingOptions	:=		# опции компилятору
    LinkingOptions	:=-lm		# опции линкеру (например, -lm)

# Продвинутые опции:

    ObjectFilesDirectory:=./obj 	# где хранить .o и .d файлы
    ManiacCompiling	:=n		# для строгого ANSI C
    CC			:=gcc		# С компилятор
    CXX			:=g++		# С++ компилятор
    Linker		:=g++		# линкер

#############################################################################
#
#   Приготовим опции

TargetName:=$(strip $(TargetName))
Debug:=$(strip $(Debug))
CompilingOptions:=$(strip $(CompilingOptions))
LinkingOptions:=$(strip $(LinkingOptions))
ObjectFilesDirectory:=$(strip $(ObjectFilesDirectory))
ManiacCompiling:=$(strip $(ManiacCompiling))

DebugCompilingOptions:=-g
ReleaseCompilingOptions:=-O3 -fexpensive-optimizations -malign-double -DNDEBUG -ffast-math
DebugLinkingOptions:=# обычно ничего не делает
ReleaseLinkingOptions:=-O3# интересно, а это что-нибудь делает?
DependencyGenerationOption:=-MMD
ManiacCompilingOptions:=-Wall -Werror -Wshadow -pedantic-errors \
    -Wpointer-arith -Waggregate-return \
    -Wstrict-prototypes -Wmissing-declarations \
    -Wlong-long -Winline -Wredundant-decls -Wcast-qual -Wcast-align \
    -D__STRICT_ANSI__

# Теперь варианты

ifeq ($(Debug),y)
    CompilingOptions+=$(DebugCompilingOptions)
    LinkingOptions+=$(DebugLinkingOptions)
else
    CompilingOptions+=$(ReleaseCompilingOptions)
    LinkingOptions+=$(ReleaseLinkingOptions)
endif

ifeq ($(ManiacCompiling),y)
    CompilingOptions+=$(ManiacCompilingOptions)
endif

#############################################################################
#
# Сами правила

# Найдем исходники
FilesSuffix1:=.c
FilesSuffix2:=.cpp
FilesSuffix1:=$(strip $(FilesSuffix1))
FilesSuffix2:=$(strip $(FilesSuffix2))

SourceFiles1:=$(wildcard *$(FilesSuffix1))
SourceFiles2:=$(wildcard *$(FilesSuffix2))
ObjectFiles:=$(SourceFiles1:%$(FilesSuffix1)=$(ObjectFilesDirectory)/%.o)
ObjectFiles+=$(SourceFiles2:%$(FilesSuffix2)=$(ObjectFilesDirectory)/%.o)
DependencyFiles:=$(ObjectFiles:%.o=%.d)

.PHONY: clean rebuild

$(TargetName): $(ObjectFiles) Makefile
	@echo linking
	@$(Linker) $(ObjectFiles) $(LinkingOptions) -o $(TargetName)
	@echo "(Compiling options: $(CompilingOptions))"
	@echo "(Linking options: $(LinkingOptions))"
ifeq ($(Debug),n)
	strip $(TargetName)
endif
# В следующей строке проверка, в терминал мы пишем или нет.
	@if [ -t 1 ]; then echo "[1;32mSuccess[0;m"; else echo Success!; fi

$(ObjectFilesDirectory)/%.o: %$(FilesSuffix1) Makefile
	@mkdir -p $(ObjectFilesDirectory)
	@echo compiling $<
	@$(CC) $(DependencyGenerationOption) $(CompilingOptions) -c -o $@ $<

$(ObjectFilesDirectory)/%.o: %$(FilesSuffix2) Makefile
	@mkdir -p $(ObjectFilesDirectory)
	@echo compiling $<
	@$(CXX) $(DependencyGenerationOption) $(CompilingOptions) -c -o $@ $<

clean:
	rm -rf $(ObjectFilesDirectory) $(TargetName)

rebuild: clean $(TargetName)

-include $(DependencyFiles)
