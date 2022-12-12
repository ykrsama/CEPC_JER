#! /bin/bash
unset MARLIN_DLL
source /cvmfs/cepc.ihep.ac.cn/software/cepcenv/setup.sh
#cepcenv use 0.1.0-rc9
#. /besfs/groups/higgs/Software/v01-17-05_slc6/init_ilcsoft_151105.sh
PACKAGEDIR=/workfs2/cepc/xuliang/processor/GenJet/build-debug
export MARLIN_DLL=$MARLIN_DLL:${PACKAGEDIR}/lib/libmWMeasurement.so
export MARLIN_DLL=$MARLIN_DLL:${PACKAGEDIR}/lib/libFSClasser.so
