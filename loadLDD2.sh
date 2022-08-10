#! /bin/bash
unset MARLIN_DLL
source /cvmfs/cepc.ihep.ac.cn/software/cepcenv/setup.sh
cepcenv use 0.1.0-rc9
#. /besfs/groups/higgs/Software/v01-17-05_slc6/init_ilcsoft_151105.sh
export MARLIN_DLL=$MARLIN_DLL:/cefs/higgs/pzlai/JES/Product/Product_qqH_h_240/build/lib/libmWMeasurement.so

export MARLIN_DLL=$MARLIN_DLL:/cefs/higgs/pzlai/JES/Product/qqH_h_240_FSClasser/FSClasser/lib/libFSClasser.so

