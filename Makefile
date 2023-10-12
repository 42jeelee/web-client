NAME     :=  client

CXX      :=  C++
CXXFLAGS :=  -Wall -Wextra -Werror -std=c++98

INCDIR   :=  ./includes
SRCSDIR  :=  ./srcs

SRCS     :=  $(wildcard $(SRCSDIR)/*.cpp)
OBJS     :=  $(SRCS:.cpp=.o)

$(NAME)  :   $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o      :  %.cpp
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

all      :
	@$(MAKE) $(NAME)

clean    :
	@$(RM) $(OBJS)

fclean   :  clean
	@$(RM) $(NAME)

re       :
	@make fclean
	@make all

.PHONY   : all clean fclean re