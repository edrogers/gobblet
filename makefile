# Makefile

php_gobblet : phpmain.c human.c PhpBot.c move.c square.c board.c \
		     	human.h PhpBot.h move.h square.h board.h
	keychain --nogui /home/ed/.ssh/dd4550; \
	. ${HOME}/.keychain/`hostname`-sh; \
	rsync -avz -e "ssh -p 53704" ${HOME}/CVS/ "ed@hbar.mine.nu:~/CVS/"
	g++ -o php_gobblet phpmain.c human.c square.c move.c PhpBot.c board.c minmaxBot.c

gobblet : main.c human.c alphaBot.c betaBot.c Bot.c move.c square.c board.c \
		 human.h alphaBot.h betaBot.h Bot.h move.h square.h board.h
	keychain --nogui /home/ed/.ssh/dd4550; \
	. ${HOME}/.keychain/`hostname`-sh; \
	rsync -avz -e "ssh -p 53704" ${HOME}/CVS/ "ed@hbar.mine.nu:~/CVS/"
	g++ -o gobblet main.c betaBot.c human.c alphaBot.c square.c move.c Bot.c board.c minmaxBot.c
