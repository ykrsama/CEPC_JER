# .bashrc

# Source global definitions
#if [ -f /etc/bashrc ]; then
#        . /etc/bashrc
#fi

PS1="\n\[\033[35m\]\$(/bin/date)\n\[\033[32m\]\w\n\[\033[1;31m\]\u@\h: \[\033[1;34m\]\$(/usr/bin/tty | /bin/sed -e 's:/dev/::'): \[\033[1;36m\]\$(/bin/ls -1 | /usr/bin/wc -l | /bin/sed 's: ::g') files \[\033[1;33m\]\$(/bin/ls -lah | /bin/grep -m 1 total | /bin/sed 's/total //')b\[\033[0m\] -> \[\033[0m\]"
PS1="[\[\033[32m\]\w]\[\033[0m\]\n\[\033[1;36m\]\u\[\033[1;33m\]:) \[\033[0m\]"
PS1="\n\[\e[32;1m\](\[\e[37;1m\]jobs:\j\[\e[32;1m\])-( \[\e[37;1m\]\w\[\e[32;1m\] )\n( \[\e[37;1m\]\!\[\e[32;1m\] )-> \[\e[0m\]"
PS1="[\@]: \w\$ "
# User specific aliases and functions

alias ls='ls --color'
alias ll='ls -ltr'
alias cp='cp -iuv'
alias mv='mv -iuv'
alias rm='rm -iv'
alias ssh='ssh -X'
alias dvipdf='dvipdf -sPAPERSIZE=a4'
alias screen="/workfs/bes/lig/bin/local/bin/screen"

alias qsub='qsub -me -M LI.Gang@mail.ihep.ac.cn'
alias qc='~/bin/python/qcount'
alias clean='~/bin/clean'
alias dif2='~/bin/python/dif2.py'
alias axel='/panfs/panfs.ihep.ac.cn/home/data/lig/local/bin/axel'
alias twobody='~/bin/python/twobody.py'
alias threebody='~/bin/python/threebody.py'
alias significance='~/config/util/significance/significance'
alias qkill='~/bin/qkill'
alias killQ='~/bin/killQ'
alias kill0='~/bin/kill0'
alias error='~/bin/system.py'
alias ruby='/ihepbatch/besd11/lig/local/bin/ruby'
alias v='vim    '
alias shli='$HOME/bin/python/shli'
alias kili='$HOME/bin/python/shli kill '
alias renew='$HOME/bin/renew.csh        '
alias vi='vim '
alias m='less'
alias pdf='acroread'
alias get='wget -c -t 0'
alias lt='ls -thrl '
alias rm='rm -iv'
alias cp='cp -iv'
alias mv='mv -iv'
alias du='du -h'
alias dug='du -cs -B 1073741824 *'
alias df='df -h'
alias gv='gv -scale 0.8'
alias ls='ls --color -F -h'
alias cl='clear'
alias bye='exit'
alias root='root -l '
alias ilcsoft='.  /besfs/groups/higgs/Software/v01-17-05/init_ilcsoft_v01-17-05_default_lcfiplus.sh'
alias ilc='.      /besfs/groups/higgs/Software/v01-17-05/init_ilcsoft_v01-17-05_default_lcfiplus.sh'
alias ilc6='.     /besfs/groups/higgs/Software/v01-17-05_slc6/init_ilcsoft_151105.sh'
alias ilc618='.     /besfs/groups/higgs/Software/v01-17-05_slc6/init_ilcsoft_root.5.34.18.sh'
alias ilc16='.    ~/config/ilcsoft/init_ilcsoft_v01-16.sh'
alias code='cd /workfs/bes/lig/higgs/FSClasser; ls  '
alias lib='cd /afs/ihep.ac.cn/soft/common/gcc/v01-17-05; ls  '
alias ft='cd /besfs/groups/higgs/users/lig/analysis/LCFIplus; ls  '
alias dt='cd /besfs/groups/higgs/data/SimReco/wo_BS/CEPC_v4/; ls  '
alias acts='cd /cefs/higgs/lig/ACTS-related/test_install_acts/acts-fw; source /cefs/higgs/lig/ACTS-related/test_install_acts/acts-core/CI/setup_lcg94.sh'
alias mokka_xy='. ~/config/ilcsfot/mokka_xy.sh'
alias initwhizard="source ~/config/ilcsoft/init_whizard222.sh"
alias cepcgaudi="source ~/bin/cepcGaudi"
#. init_ilcsoft_v01-17-05.sh 
export _JAVA_OPTIONS="-Xmx128m" # to solve the problem of NOT ENOUGH MEMORY FOR Java Virtual Machine
export PATH="${PATH}:/afs/ihep.ac.cn/soft/common/sysgroup/hep_job/bin/:."
