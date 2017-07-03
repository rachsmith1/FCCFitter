for ene in 5 10 15 20 25 30 35 40 45 50;
do

    ./myFit.exe h config_FCC/Zprime_ll_fcc_v01/Zprime_mumu_"$ene"TeV.config
    ./myFit.exe w config_FCC/Zprime_ll_fcc_v01/Zprime_mumu_"$ene"TeV.config
    ./myFit.exe f config_FCC/Zprime_ll_cms/Zprime_ee_"$ene"TeV.config
    ./myFit.exe d config_FCC/Zprime_ll_fcc_v01/Zprime_mumu_"$ene"TeV.config
    ./myFit.exe p config_FCC/Zprime_ll_fcc_v01/Zprime_mumu_"$ene"TeV.config
    ./myFit.exe l config_FCC/Zprime_ll_fcc_v01/Zprime_mumu_"$ene"TeV.config
    #./myFit.exe s config_Zprime_ll/Zprime_mumu_"$ene"TeV.config

    #mv Zprime_mumu_"$ene"TeV Outputs/Zprime/mumu/

done

