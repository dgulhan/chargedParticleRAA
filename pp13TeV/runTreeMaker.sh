export SCRAM_ARCH=slc6_amd64_gcc491
source /osg/app/cmssoft/cms/cmsset_default.sh

cd  /net/hisrv0001/home/dgulhan/CMSSW_7_5_3_patch1/src
eval `scramv1 runtime -sh`
cd -

echo | awk -v dataset=$1 -v infile=$2 -v outfile=$4 '{print "./makeTrackTreeByHLT.exe \""dataset"\" \""infile"\" \""outfile"\""}' | bash

mv $4 $3