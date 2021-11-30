#### define o compilador
CPPC = g++
#############################

#### opcoes de compilacao e includes
#CCOPT = -O3 -fPIC -fexceptions -DNDEBUG -DIL_STD -std=c++11
CCOPT = -O3 -fexceptions -Werror -std=c++11
CONCERTINCDIR = $(CONCERTDIR)/include
#############################

#### diretorios com os source files e com os objs files
SRCDIR = src
OBJDIR = obj
#############################

#### lista de todos os srcs e todos os objs
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))
#############################

#### regra principal, gera o executavel
vnd: $(OBJS) 
	@echo  "Linking all objects files: "
	$(CPPC) $(CCOPT) $(OBJS) -o $@
############################

#inclui os arquivos de dependencias
-include $(OBJS:.o=.d)

#regra para cada arquivo objeto: compila e gera o arquivo de dependencias do arquivo objeto
#cada arquivo objeto depende do .c e dos headers (informacao dos header esta no arquivo de dependencias gerado pelo compiler)
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@echo  "Compiling $<: "
	$(CPPC) $(CCFLAGS) -c $< -o $@
	@echo  "creating $< dependency file: "
	$(CPPC) -std=c++11  -MM $< > $(basename $@).d
	@mv -f $(basename $@).d $(basename $@).d.tmp #proximas tres linhas colocam o diretorio no arquivo de dependencias (g++ nao coloca, surprisingly!)
	@sed -e 's|.*:|$(basename $@).o:|' < $(basename $@).d.tmp > $(basename $@).d
	@rm -f $(basename $@).d.tmp

#cria o arquivo de assembly gerado
%.as: %.c ${SRCDIR}
	${CPPC} ${CCOPT} -S -o $@ $<

#delete objetos e arquivos de dependencia
clear:
	@echo "cleaning obj directory "
	@rm vnd -f $(OBJDIR)/*.o $(OBJDIR)/*.d $(OBJDIR)/*.asm


rebuild: clean vnd