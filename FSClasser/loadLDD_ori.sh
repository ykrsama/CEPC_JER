unset MARLIN_DLL
. /besfs/groups/higgs/Software/v01-17-05_slc6/init_ilcsoft_151105.sh
export FSClasser_HOME=/cefs/higgs/pzlai/JES/Product/Product_zz_sl_240/FSClasser
export LD_LIBRARY_PATH="$FSClasser_HOME/lib:$LD_LIBRARY_PATH"
export MARLIN_DLL=$MARLIN_DLL:$FSClasser_HOME/lib/libFSClasser.so

