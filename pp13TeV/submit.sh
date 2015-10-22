#!/bin/sh


version=1
dataset=/mnt/hadoop/cms/store/user/dgulhan/JetHT/HiForest_pp13TeV_JetHT_Run2015D_PromptReco_v3/6ad7619280763eb51bd217a6545ce408/
destination=/mnt/hadoop/cms/store/user/dgulhan/CPR/pp13TeV/20151015_v2/

NAME="makeTrackTreeByHLT.C"
g++ $NAME $(root-config --cflags --libs) -O2 -o "${NAME/%.C/}.exe"

subdir=`date +%Y%m%d`
logdir=/net/hisrv0001/home/dgulhan/logsCPR/${subdir}_v3
mkdir $logdir

mkdir -p $destination

for file in ${dataset}/HiForest_*
  do
      cropped=`echo $file | sed "s/\// /g" | awk '{ print $10 }'`
	  
	  outfile=hltTree_${cropped}
      Error=`echo $outfile | sed "s/root/err/g"`
	  Output=`echo $outfile | sed "s/root/out/g"`
	  Log=`echo $outfile | sed "s/root/log/g"`        
	  	
	      echo "Output is : $outfile"
	      echo "Error is : $Error"
	      echo "LFN is : $lfn"
	      echo "----------------------"
	      
	      cat > subfile <<EOF

Universe       = vanilla

# files will be copied back to this dir
Initialdir     = .

# run my script
Executable     = runTreeMaker.sh

+AccountingGroup = "group_cmshi.yetkin"
#+IsMadgraph = 1

Arguments      = $dataset $cropped $destination $outfile \$(Process)
# input files. in this case, there are none.
Input          = /dev/null

# log files
Error          = $logdir/$Error
Output         = $logdir/$Output
Log            = $logdir/$Log

# get the environment (path, etc.)
Getenv         = True

# prefer to run on fast computers
Rank           = kflops


# should write all output & logs to a local directory
# and then transfer it back to Initialdir on completion
should_transfer_files   = YES
when_to_transfer_output = ON_EXIT
# specify any extra input files (for example, an orcarc file)
transfer_input_files    = makeTrackTreeByHLT.exe,list_triggers.txt

Queue
EOF

# submit the job
condor_submit subfile

done



