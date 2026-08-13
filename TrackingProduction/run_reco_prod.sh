#!/bin/bash

export USER="$(id -u -n)"
export LOGNAME=${USER}
export HOME=/sphenix/u/${LOGNAME}

source /sphenix/u/mitrankova/.login_PR_TPC_SA

nEvents="$1"
jobindex="$2"



#segment=$(( jobindex / 2 ))
#nSkip=$(( (jobindex % 2) * 5000 ))
nSkip=0
segment=$jobindex
runnumber=79513
collision="run3pp"
cdbtag="ana532_nocdbtag_v001"

OutDir=/sphenix/tg/tg01/hf/mitrankova/79513_TPC_SA_Matched_10000
name="TPC_SA_Matched"

echo ========================================================
echo Running Fun4All_raw_hit_TPC_Matched_reco.C
echo "  Condor job index    = ${jobindex}"
echo "  nEvents             = ${nEvents}"
echo "  nSkip               = ${nSkip}"
echo "  Run Number          = ${runnumber}"
echo "  Segment             = ${segment}"
echo "  OutDir              = ${OutDir}"
echo "  collision           = ${collision}"
echo "  cdbtag              = ${cdbtag}"
echo "  name                = ${name}"
echo ".x Fun4All_raw_hit_TPC_Matched_reco.C(${nEvents},${runnumber},${segment},\"${OutDir}\",${nSkip},\"${collision}\",\"${cdbtag}\",\"${name}\")"
echo ========================================================

root.exe -l -b << EOF
.x Fun4All_raw_hit_TPC_Matched_reco.C(${nEvents},${runnumber},${segment},"${OutDir}",${nSkip},"${collision}","${cdbtag}","${name}")
EOF

echo all done