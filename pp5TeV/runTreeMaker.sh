# export SCRAM_ARCH=slc6_amd64_gcc491
# source /osg/app/cmssoft/cms/cmsset_default.sh

# cd  /net/hisrv0001/home/dgulhan/CMSSW_7_5_3_patch1/src
# eval `scramv1 runtime -sh`
# cd -

tar -zxvf corr.tar.gz
dir=/data/velicanu/store/group/phys_heavyions/velicanu/forest/Run2015E/ExpressPhysics/Merged/

file[0]=ExpressHiForest_run262163_277k.root
file[1]=ExpressHiForest_run262163_100k.root
file[2]=ExpressHiForest_run262167_473k.root
file[3]=ExpressHiForest_run262171_266k.root
file[4]=ExpressHiForest_run262172_261k.root

for ifile in `seq 0 4`
 do
 output=out_${file[$ifile]}

  echo | awk -v dataset=$dir -v infile=${file[$ifile]} -v outfile=$output '{print "./makeTrackTreeByHLT.exe \""dataset"\" \""infile"\" \""outfile"\""}' | bash

  mv $4 $3
 done
rm -r trkCorrections