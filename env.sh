
export MARLIN=/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/Marlin/v01-05
export LCIO=/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/lcio/v02-04-03
export ROOTSYS=/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/root/5.34.07
export DRUIDDIR=/afs/ihep.ac.cn/users/m/manqi/Software/Druid_SL6
export PATH=/usr/lib64/qt-3.3/bin:/usr/kerberos/sbin:/usr/kerberos/bin:/bin:/usr/bin:/usr/externals/bin:/usr/sbin:/usr/local/bin:/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/sbin:/usr/java/latest/bin:$MARLIN/bin:$ROOTSYS/bin:$DRUIDDIR/bin:$LCIO/bin:$PATH
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$ROOTSYS/lib:$LCIO/lib

alias HFcmake='cmake -C /afs/ihep.ac.cn/soft/common/gcc/v01-17-05/ILCSoft.cmake ..'
