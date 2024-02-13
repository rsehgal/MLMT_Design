#!/bin/sh
gun=$1
nparticles=$2
for ener in {1000..10000..1000}
do
outfile=$gun'_'$ener'
sed 's/ENER/'$ener'/g' shielding.mac > $outfile 
sed 's/GUN/'$gun'/g' -i $outfile
sed 's/NPARTICLES/'$nparticles'/g' -i $outfile
echo $outfile
./main $outfile &
done
