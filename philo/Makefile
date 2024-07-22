NAME			:=	philo

INCPATH			:=	-I inc

FILES			:=	\
					utils.c			\
					fork.c			\
					philo.c			\
					parsing.c		\
					thread.c		\
					monitor_init.c	\
					monitor.c		\
					main.c			\

SRCPATH			:=	src
SRC				:=	$(addprefix $(SRCPATH)/,$(FILES))

OBJPATH			:=	obj
OBJ				:=	$(addprefix $(OBJPATH)/,$(FILES:.c=.o))

DEFAULT			:=	"\033[0m"
YELLOW			:=	"\033[0;33m"
RED				:=	"\033[0;31m"
GREEN			:=	"\033[0;32m"

CC				:=	cc
RM				:=	rm -f
CFLG			:=	-Wall -Werror -Wextra

all				:	$(NAME)

$(OBJPATH)		:
					@mkdir $@

$(NAME)			:	$(OBJPATH) $(OBJ)
					@$(CC) $(OBJ) -o $(NAME)
					@echo -n $(YELLOW)
					@echo -n "$(NAME) created"
					@echo $(GREEN)
					@sleep 0.3
					@echo "Project successfully compiled"
					@echo -n $(DEFAULT)

$(OBJPATH)/%.o	:	$(SRCPATH)/%.c
					@sleep 0.1
					@$(CC) $(CFLG) -c $< -o $@ $(INCPATH)
					@printf "%s\n" $<

.PHONY			:	all re fclean clean

re				:	fclean all

clean			:
					@echo -n $(RED)
					@$(RM) $(OBJ)
					@$(RM) -r $(OBJPATH)
					@echo "Removed the object files and obj folder..."
					@sleep 0.2
					@echo -n $(DEFAULT)

fclean			:	clean
					@echo -n $(RED)
					@$(RM) $(NAME)
					@echo "Removed $(NAME)"
					@echo -n $(DEFAULT)
					@sleep 0.2
