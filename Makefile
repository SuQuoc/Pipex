NAME		= pipex
ARGV		= infile "ls -l" "wc -l" outfile
DYN_ARGV		= infile "ls -l" "grep x" outfile
DYN_ARGV		= infile "ls -l" "grep x" "sort" outfile
DYN_ARGV		= infile "ls -l" "grep x" "sort" "wc -w" outfile

HD_INP			= "cat" "wc -w" outfile

ORI_ARGV		= < infile grep a1 | wc -w > outfile
ORI_ARGV		= < infile ls -l | grep x | sort | wc -w > outfile


CC			= cc
CFLAGS		= -Wall -Werror -Wextra

SRC_PATH 	= src
OBJ_PATH 	= obj

SRC			= 	main.c \
				children.c\
				exe_cmd.c\
				s_tier.c\
				heredoc_bonus.c\
				exiting_program.c
#main.c

SRCS 		= $(addprefix $(SRC_PATH)/, $(SRC))
OBJ 		= $(SRC:.c=.o)
OBJS 		= $(addprefix $(OBJ_PATH)/, $(OBJ))

LIBFT_DIR 	= libft
LIBFT 		= $(LIBFT_DIR)/libft.a

TEST		= $(SRC_PATH)/tests.c


.PHONY: all bonus clean fclean re aa aac va seelib norm normb
all: $(OBJ_PATH) $(NAME)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) 
	@echo "$(GREEN)Executable \"$(NAME)\" succesfully created.$(NC)"


$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)


#Project specific
test: clean 
	$(CC) $(CFLAGS) $(TEST) $(LIBFT)

ori: reset
	$(ORI_ARGV)
	
reset:
	@echo "$(YELLOW)Clearing in- and outfile contents$(NC)"  
	echo "a1 a1 a1 a1" > infile
	echo "" > outfile

hd: re reset
	rm -f .here_doc.tmp
	./$(NAME) here_doc EOF $(HD_INP)


#General
clean:
	rm -rf $(OBJ_PATH)
	@echo "$(MAGENTA)Obj directory removed.$(NC)"
	$(MAKE) -C $(LIBFT_DIR) clean
	@echo "$(MAGENTA)Make clean in directory "$(LIBFT_DIR)" invoked.$(NC)"

fclean: clean
	rm -f $(NAME)
	@echo "$(MAGENTA)Deleted executable named: $(NAME)$(NC)"
	$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "$(MAGENTA)Make fclean in directory "$(LIBFT_DIR)" invoked.$(NC)"

re: fclean all
	@echo "$(GREEN)Recompilation successfully done!$(NC)"

aa: re
	@echo "$(GREEN)Executing programm with \"TEST_INPUT\" of the Makefile.$(NC)"
	./$(NAME) $(ARGV)


aab: re reset
	@echo "$(GREEN)Executing programm with \"TEST_INPUT\" of the Makefile.$(NC)"
	./$(NAME) $(DYN_ARGV)

va: re
	valgrind --leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	./$(NAME) $(DYN_ARGV)

#--trace-children=yes
#valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) $(TEST_INPUT)

debug : CFLAGS += -g
debug : fclean all

seelib:
	@ar -t $(NAME)

norm: $(SRCS)
	norminette -R CheckForbiddenSourceHeader $(SRCS) $(NAME).h
	@echo "$(BWHITE)All source files checked with norminette.$(NC)"









#--------COLORS---------------------------------#
RED			=	\033[0;31m
GREEN		=	\033[0;32m
YELLOW		=	\033[0;33m
BLUE 		=	\033[0;34m
MAGENTA 	=	\033[0;35m
CYAN 		=	\033[0;36m
WHITE		=	\033[0;37m
NC			=	\033[0m


#-------BOLD COLORS-----------------------------#
BRED		=	\033[1;31m
BGREEN		=	\033[1;32m
BYELLOW		=	\033[1;33m
BBLUE 		=	\033[1;34m
BMAGENTA 	=	\033[1;35m
BCYAN 		=	\033[1;36m
BWHITE		=	\033[1;37m
