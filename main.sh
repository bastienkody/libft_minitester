#! /bin/bash

# clone into libft repo and just : 
# cd libft_minitester/ && bash main.sh

#turn bool_ to 0 to skip specific tests
bool_compliance=1
bool_bonus=1
bool_print_tips=1
lib_bonus="libft.a"
rule_bonus="bonus"

# compil infos
cc=gcc
cflags="-Wall -Wextra -Werror"
ldflags="../libft.a -static"

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
[[ $(uname) != "Linux" ]] && echo -e "${ITA}Possibly uncompatible os ($(uname))${END}"

# ------------------------------------------------------------------------------
# 				----- NORM, MAKEFILE and FORBIDDEN STUFF -----
# ------------------------------------------------------------------------------
if [[ $bool_compliance == 1 ]] ; then 
echo -e "${YEL_BG}CCOMPLIANCE${END}"

#------------------------------
# check all expected files :
echo -ne "${BLU_BG}Expected files${END}\t\t"

basename -a $(ls -l ../*.c ../*.h ../Makefile | awk '{print $NF}' ) > tmp_expected_files.txt

if [[ $( diff tmp_expected_files.txt filestest/expected_files.txt &>/dev/null ; echo $? ) == 0 ]] ; then
	echo -e "${GREEN}Found all${END}"
	rm tmp_expected_files.txt
else
	echo ""
	while read -r line
	do	if [[ ! $(grep $line filestest/expected_files.txt) ]] ; then
		echo -e "${RED}Unexpected $line${END}" ; fi ;
	done < tmp_expected_files.txt

	while read -r line
	do	if [[ ! $(grep $line tmp_expected_files.txt) ]] ; then
		echo -e "${RED}Missing $line${END}" ; fi ;
	done < filestest/expected_files.txt
fi

#----------
# norminette
echo -ne "${BLU_BG}Test norminette${END}\t\t"
norm=$(norminette ../*.c ../*.h)
if [[ $(echo "$norm" | egrep -v "OK\!$") ]] ;
then
	echo -e "${RED}norme errors:${END}"
	echo -e "$norm" | egrep -v "OK\!$"
else
	echo -e "${GREEN}norm ok${END}"
fi

#---------------
# makefile relink
echo -ne "${BLU_BG}Test Makefile${END}\t\t"
make re -C ../ 1>/dev/null 2> stderrmake.txt
make --no-print-directory -C ../ > stdoutmakebis.txt 2>&1
[[ -s stderrmake.txt ]] && echo -ne "${RED}make wrote on std err${END}" || echo -ne "${GREEN}no make error${END}" 
echo -n " -- "
cat stdoutmakebis.txt | egrep -viq "(nothin|already|date)" && echo -ne "${RED}makefile relink?${END}" || echo -ne "${GREEN}no relink${END}"
echo -n " -- "
[[ -f ../libft.a ]] && echo -e "${GREEN}libft.a found${END}" || { echo -e "${RED}no libft.a found. Tester exiting.${END}" && exit 1 ; }
rm -rf stderrmake.txt stdoutmakebis.txt

#------------
# relink bonus
if [[ $bool_bonus == 1 ]] ; then
echo -ne "${BLU_BG}Test Makefile bonus${END}\t"
make fclean -C ../ &>/dev/null && make ${rule_bonus} -C ../ 1>/dev/null 2> stderrmake.txt
make ${rule_bonus} --no-print-directory -C ../ > stdoutmakebis.txt 2>&1
[[ -s stderrmake.txt ]] && echo -ne "${RED}make ${rule_bonus} wrote on std err${END}" || echo -ne "${GREEN}no make ${rule_bonus} error${END}" 
echo -ne " -- "
cat stdoutmakebis.txt | egrep -viq "(nothin|already|date)" && echo -ne "${RED}makefile relinks on bonus?${END}" || echo -ne "${GREEN}no relink on bonus${END}"
echo -ne " -- "
[[ -f ../$lib_bonus ]] && echo -e "${GREEN}$lib_bonus${END}" || echo -e "${RED}$lib_bonus not found${END}"
rm -rf stderrmake.txt stdoutmakebis.txt
( make fclean -C ../ && make -C ../ ) >/dev/null 2>&1
fi

#-------------------------
# makefile : flags and rule
echo -ne "${BLU_BG}Makefile flags${END}\t\t"
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

#------------------------------
# forbidden : libtool and global
echo -ne "${BLU_BG}Forbidden stuff${END}\t\t"
grep -sq "libtool" ../Makefile && echo -e "${RED}libtool in Makefile??? Please use ar${END}" && exit 2
grep -sq -- "-std=c99" ../Makefile && echo -e "${RED}-std=99 flag forbidden${END}" && exit 2
echo ../*.c ../*.h | grep -sq global && echo -e "${RED}global variable???${END}" && exit 2
echo -e "${GREEN}OK${END}"

else
make -C ../ >/dev/null 
fi

# ------------------------------------------------------------------------------
# 					------- MANDATORY FUNCTIONS TESTS -------
# ------------------------------------------------------------------------------
echo -e "${YEL_BG}MANDATORY FUNCTION TESTS${END}"

#-----------------------------
# putchar/str functions 
echo -ne "${BLU_BG}Put_chastr functions${END}\t"

$cc $cflags filestest/put_chastr.c $ldflags
./a.out > ft_out 2> ft_err && rm a.out
echo -n aAyoubidoubidouyouhouuuu > std_out && echo immakinminimalwagemama >> std_out
echo "uUskudara gideriken" > std_err && echo aldidabiryamur >> std_err

if [[ $(diff std_out ft_out &>/dev/null ; echo $?) == 0 ]] && [[ $(diff std_err ft_err &>/dev/null ; echo $?) == 0 ]] ; then
	echo -e "${GREEN}OK${END}" 
	rm std_out std_err ft_out ft_err 
else 
	echo -e "${RED}KO, check logfile (libft : ft_out/err vs expected : std_out/err)${END}"
fi

#-----------------------------
# putnbr 
echo -ne "${BLU_BG}Put_nbr${END}\t\t\t"

$cc $cflags filestest/put_nbr.c $ldflags
./a.out > ft_outnb 2> ft_errnb && rm a.out
echo "2147483647" > std_outnb && echo "-2147483648" >> std_outnb
echo 0 > std_errnb && echo -1 >> std_errnb && echo 12345678 >> std_errnb

if [[ $(diff std_outnb ft_outnb &>/dev/null ; echo $?) == 0 ]] && [[ $(diff std_errnb ft_errnb &>/dev/null ; echo $?) == 0 ]] ; then
	echo -e "${GREEN}OK${END}" 
	rm std_outnb ft_outnb std_errnb ft_errnb
else 
	echo -e "${RED}KO, check logfile (libft : ft_outnb/errnb vs expected : std_outnb/errnb)${END}"
fi

#-----------------------------
# one char functions (vs libc)
echo -e "${BLU_BG}One char functions${END}"

$cc $cflags filestest/one_char_functions.c $ldflags
./a.out && rm a.out

#---------------
# atoi (vs libc)
echo -e "${BLU_BG}Atoi${END}"

$cc $cflags filestest/atoi.c $ldflags
./a.out && rm a.out

#---------------
# itoa
echo -e "${BLU_BG}Itoa${END}"

$cc $cflags filestest/itoa.c $ldflags
./a.out && rm a.out

#--------------------------------
# mem :  (vs libc)
echo -e "${BLU_BG}Mem functions${END}"

$cc $cflags filestest/mem.c $ldflags
./a.out && rm a.out

#-------------------------------------------
# str p1: len, chr, rchr, ncmp, nstr (vs libc)
echo -e "${BLU_BG}Str libc part 1${END}"

$cc $cflags filestest/str1.c $ldflags -lbsd
./a.out && rm a.out

#--------------------------------
# str p2: dup, lcat, lcpy (vs libc)
echo -e "${BLU_BG}Str libc part 2${END}"

$cc $cflags filestest/str2.c $ldflags -lbsd
./a.out && rm a.out

#--------------------------------
# str p3: join, trim, sub, split
echo -e "${BLU_BG}Str part 3${END}"

$cc $cflags filestest/str3.c $ldflags
./a.out && rm a.out

#--------------------------------
# str p4: ptr sur fct
echo -e "${BLU_BG}Str part 4 (ptr sur fct)${END}"

$cc $cflags filestest/str4.c $ldflags
./a.out && rm a.out

# ------------------------------------------------------------------------------
# 					------- BONUS FUNCTIONS TESTS -------
# ------------------------------------------------------------------------------
if [[ $bool_bonus == 1 ]] ; then 
make bonus -C ../ &>/dev/null
echo -e "${YEL_BG}BONUS FUNCTION TESTS${END}"

#--------------------------------
# bonus : all in one
echo -ne "${BLU_BG}One test for all${END}"

$cc $cflags filestest/bonus_all_in_one.c $ldflags
./a.out > libft_bonus && rm a.out

echo "CCC" > expected_bonus
echo "DDD" >> expected_bonus
echo "BBB CCC DDD " >> expected_bonus
echo "0" >> expected_bonus
echo "DDD EEE FFF " >> expected_bonus
echo "1" >> expected_bonus

if [[ $(diff libft_bonus expected_bonus &>/dev/null ; echo $?) == 0 ]] ; then
	echo -e "${GREEN}\tOK${END}" 
	rm libft_bonus expected_bonus
else 
	echo -e "${RED}\tKO, check logfile (libft_bonus and expected_bonus)${END}"
fi
echo "------------------------------------"
fi

# ------------------------------------------------------------------------------
# 					------- OUTRO -------
# ------------------------------------------------------------------------------
make fclean -C ../ &>/dev/null
if [[ $bool_bonus == 0 ]] ; then 
exit 0
fi

echo '
## Few tips for new studs ##

Makefile	:	not to relink -> rule == name of exec (bonus is fucked up)
Makefile	:	add header in dependances of name rule
Makefile	:	@ not to print current line ; use echo "\033[m" for format/color
Makefile	:	make -C <path> to call specific Makefile (printf, gnl etc)
Makefile	:	@make --no-print-directory -C -> no print when making elsewhere
Libft		:	atoi overflow (int:pushswap, long long:exitminishell, uchar:cub3drgb)
Libft		:	ft_fprintf (solong, pushswap, minishell etc)
No sudo		:	mkdir ~/.bin -> put your custom exec
No sudo		:	in .bashrc = $PATH+=":~/.bin"
Stack		:	VLA vs malloc
Norm		:	several instructions in a return with "," and use of  typecast
Norm		:	silent unused with : int main(__attribute__((unused) int argc)
Norm		:	iter with i=-1; while(++i) to start at idx 0 and save 1-2lines
Leaks		: 	compile with -g3 (more info ie. line number) 
Leaks		:	set alias valgrind : 
			- alias vlgleak="vlg --leak-check=full"
			- alias vlg="/usr/bin/valgrind" (for unset PATH tests)
			- alias vlgfd="vlg--track-fds=yes --trace-children=yes" (pipex)
------------------------------------'
