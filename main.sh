#! /bin/bash

# bonus info config (turn bool_bonus to 0 if no bonus, change bonus names below)
bool_bonus=1
lib_bonus="libft.a"
rule_bonus="bonus"

cc=gcc
cflags="-Wall -Wextra -Werror"
ldflags="../libft.a"

# const
vlgleak='/usr/bin/valgrind --leak-check=full'
ITA="\033[3m"
UNDERL="\033[4m"
GREEN="\033[32m"
RED="\033[31m"
YEL="\033[33m"
END="\033[m"
BLU_BG="\033[44m"
YEL_BG="\033[43;1m"
RED_BG="\033[41;1m"

# print intro
echo "------------------------------------"
echo "------------------------------------"
echo -e "\tLIBFT MINITESTER"
echo -e "Started at $(date +%R) - $(date +"%d %B %Y")"
echo -e "by $USER on $(uname) os"
echo -e "made by bguillau (@bastienkody)"
echo "------------------------------------"
echo "------------------------------------"
[[ $(uname) != "linux" ]] && echo -e "${ITA}Possibly uncompatible os${END}"

# -----------------------------------------------------------------------------------------------------------------------------------------
# NORM, MAKEFILE and FORBIDDEN STUFF
# -----------------------------------------------------------------------------------------------------------------------------------------
echo -e "${YEL_BG}Compliance tests${END}"

#norminette
echo -ne "${BLU_BG}Test norminette:${END}\t"
norm=$(norminette ../*.c ../*.h)
if [[ $(echo "$norm" | egrep -v "OK\!$") ]] ;
then
	echo -e "${RED} norme errors:${END}"
	echo -e "$norm" | egrep -v "OK\!$"
else
	echo -e "${GREEN} norm ok${END}"
fi

#makefile relink
echo -ne "${BLU_BG}Test Makefile:${END}\t\t"
make re -C ../ 1>/dev/null 2> stderrmake.txt
make -C ../ > stdoutmakebis.txt 2>&1
[[ -s stderrmake.txt ]] && echo -ne "${RED} make wrote on std err${END}" || echo -ne "${GREEN} no make error${END}" 
echo -n " -- "
cat stdoutmakebis.txt | egrep -viq "(nothin|already|date)" && echo -ne "${RED}makefile relink?${END}" || echo -ne "${GREEN}no relink${END}"
echo -n " -- "
[[ -f libft.a ]] && echo -e "${GREEN}libft.a found${END}" || { echo -e "${RED}no libft.a found. Tester exiting.${END}" && exit 1 ; }
rm -rf stderrmake.txt stdoutmakebis.txt

#relink bonus
if [[ $bool_bonus == 1 ]] ; then
echo -ne "${BLU_BG}Test Makefile bonus:${END}\t"
make fclean -C ../ &>/dev/null && make ${rule_bonus} -C ../ 1>/dev/null 2> stderrmake.txt
make ${rule_bonus} -C ../ > stdoutmakebis.txt 2>&1
[[ -s stderrmake.txt ]] && echo -ne "${RED} make ${rule_bonus} wrote on std err${END}" || echo -ne "${GREEN} no make ${rule_bonus} error${END}" 
echo -ne " -- "
cat stdoutmakebis.txt | egrep -viq "(nothin|already|date)" && echo -ne "${RED}makefile relinks on bonus?${END}" || echo -ne "${GREEN}no relink on bonus${END}"
echo -ne " -- "
[[ -f $lib_bonus ]] && echo -e "${GREEN}$lib_bonus${END}" || echo -e "${RED}$lib_bonus not found${END}"
rm -rf stderrmake.txt stdoutmakebis.txt
( make fclean -C ../ && make -C ../ ) >/dev/null 2>&1
fi

#makefile : flags and rule
echo -ne "${BLU_BG}Makefile flags:${END}\t\t"
grep -sq -- "-Wall" ../Makefile && echo -ne "${GREEN}OK (-Wall)${END}" || echo -ne "${RED}-Wall not found${END}"
echo -n " -- "
grep -sq -- "-Wextra" ../Makefile && echo -ne "${GREEN}OK (-Wextra)${END}" || echo -ne "${RED}-Wextra not found${END}"
echo -n " -- "
grep -sq -- "-Werror" ../Makefile && echo -ne "${GREEN}OK (-Werror)${END}" || echo -ne "${RED}-Werror not found${END}"
echo -n " -- "
grep -sq "all" ../Makefile && echo -ne "${GREEN}OK (all)${END}" || echo -ne "${RED}Rule all not found${END}"
echo -n " -- "
grep -sq "clean" ../Makefile && echo -ne "${GREEN}OK (clean)${END}" || echo -ne "${RED}Rule clean not found${END}"
echo -n " -- "
grep -sq "fclean" ../Makefile && echo -ne "${GREEN}OK (fclean)${END}" || echo -ne "${RED}Rule fclean not found${END}"
echo -n " -- "
grep -sq "re" ../Makefile && echo -e "${GREEN}OK (re)${END}" || echo -e "${RED}Rule re not found${END}"

#forbidden : libtool and global
echo -ne "${BLU_BG}Forbidden stuff:${END}\t"
grep -sq "libtool" ../Makefile && echo -e "${RED}libtool in Makefile??? Please use ar${END}" && exit 2
grep -sq -- "-std=c99" ../Makefile && echo -e "${RED}-std=99 flag forbidden${END}" && exit 2
echo ../*.c ../*.h | grep -sq global && echo -e "${RED}global variable???${END}" && exit 2
echo -e "${GREEN}OK${END}"

# -----------------------------------------------------------------------------------------------------------------------------------------
# is_ functions (libc)
# -----------------------------------------------------------------------------------------------------------------------------------------
echo -e "${YEL_BG}Is_functions tests${END}"

$cc $cflags filestest/is_functions.c $ldflags
./a.out && rm a.out


