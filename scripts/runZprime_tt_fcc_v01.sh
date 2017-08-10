for ene in 2 5 10 15 20;
do
	./myFit.exe h config_FCC/Zprime_tt/fcc_v01/Zprime_tt_"$ene"TeV.config
	./myFit.exe w config_FCC/Zprime_tt/fcc_v01/Zprime_tt_"$ene"TeV.config
	./myFit.exe f config_FCC/Zprime_tt/fcc_v01/Zprime_tt_"$ene"TeV.config
	./myFit.exe d config_FCC/Zprime_tt/fcc_v01/Zprime_tt_"$ene"TeV.config
	./myFit.exe p config_FCC/Zprime_tt/fcc_v01/Zprime_tt_"$ene"TeV.config
	./myFit.exe l config_FCC/Zprime_tt/fcc_v01/Zprime_tt_"$ene"TeV.config

done
