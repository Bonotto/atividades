#directories="conf_45_LH_max conf_45_LH_tar conf_45_NN_max conf_45_NN_tar conf_65_LH_max conf_65_LH_tar conf_65_NN_max conf_65_NN_tar conf_90_LH_max conf_90_LH_tar conf_90_NN_max conf_90_NN_tar nconf_45_LH_max nconf_45_LH_tar nconf_45_NN_max nconf_45_NN_tar nconf_65_LH_max nconf_65_LH_tar nconf_65_NN_max nconf_65_NN_tar nconf_90_LH_max nconf_90_LH_tar nconf_90_NN_max nconf_90_NN_tar"
#confdirectories="conf_45_LH_max conf_45_LH_tar conf_45_NN_max conf_45_NN_tar conf_65_LH_max conf_65_LH_tar conf_65_NN_max conf_65_NN_tar conf_90_LH_max conf_90_LH_tar conf_90_NN_max conf_90_NN_tar"
#nconfdirectories="nconf_45_LH_max nconf_45_LH_tar nconf_45_NN_max nconf_45_NN_tar nconf_65_LH_max nconf_65_LH_tar nconf_65_NN_max nconf_65_NN_tar nconf_90_LH_max nconf_90_LH_tar nconf_90_NN_max nconf_90_NN_tar"

#directories="tree_45_NN_tar tree4stages_45_NN_tar transpose2tb_45_NN_tar tree_45_NN_max tree4stages_45_NN_max transpose2tb_45_NN_max"
directories="tree4stages_45_NN_max"


nb_concurrent_processes=1 #Usually use 8, but because there are only 4 we are using 4!!!
j=0

echo "INIT"

echo "Init simulation compile"

for d in $directories
do
	echo $d
	cd ./$d/vcs/
	rm logVCS.txt
	rm simv.daidir/.vcs.timestamp
	pwd
	vcs -debug_all -P ../../vcs_common/pli.tab -f ./filelist -sdf typ:SATD:sdf.sdf +neg_tchk | tee logVCS.txt &
	let j++
	cd ../../
	pwd
	((j == nb_concurrent_processes)) && { j=0; wait; }
done

echo "Simulation Compilation DONE"

echo "Init simulation"

for d in $directories
do
	echo $d
	cd ./$d/vcs/
	rm logSIMV.txt
	rm simv.daidir/.vcs.timestamp
	pwd
	./simv | tee logSIMV.txt &
	let j++
	cd ../../
	pwd
	((j == nb_concurrent_processes)) && { j=0; wait; }
done
echo "Simulation Compilation DONE"


echo "DONE"