/*

Write a program that takes one or more strings and, for each argument, puts
the last character that is a letter of each word in uppercase and the rest
in lowercase, then displays the result followed by a \n.

A word is a section of string delimited by spaces/tabs or the start/end of the
string. If a word has a single letter, it must be capitalized.

A letter is a character in the set [a-zA-Z]

If there are no parameters, display \n.

Examples:

$> ./rstr_capitalizer | cat -e
$
$> ./rstr_capitalizer "a FiRSt LiTTlE TESt" | cat -e
A firsT littlE tesT$
$> ./rstr_capitalizer "SecONd teST A LITtle BiT   Moar comPLEX" "   But... This
iS not THAT COMPLEX" "     Okay, this is the last 1239809147801 but not    the
least    t" | cat
        -e seconD tesT A littlE biT   moaR compleX$ but... thiS iS noT
thaT compleX$ okay, thiS iS thE lasT 1239809147801 buT noT    thE leasT    T$
*/
#include <unistd.h>


int	main(int argc, char **argv) {
  if (argc == 2) {
    int i = 0;
    while (argv[1][i]) {
      if ((argv[1][i] >= 'A' && argv[1][i] <= 'Z'))
        argv[1][i] += 32;
      if ((argv[1][i] >= 'a' && argv[1][i] <= 'z') &&
          (argv[1][i + 1] == '\0' || argv[1][i + 1] == ' ' ||
           argv[1][i + 1] == '\t'))
        argv[1][i] -= 32;
      write(1, &argv[1][i++], 1);
    }
  }
  write(1, "\n", 1);

  return (0);
}