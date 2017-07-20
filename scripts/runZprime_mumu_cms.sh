for ene in 5 10 15 20 25 30 35 40 45 50;
do

    ./myFit.exe h config_FCC/Zprime_ll/cms/Zprime_mumu_"$ene"TeV.config
    ./myFit.exe w config_FCC/Zprime_ll/cms/Zprime_mumu_"$ene"TeV.config
    ./myFit.exe f config_FCC/Zprime_ll/cms/Zprime_mumu_"$ene"TeV.config
    ./myFit.exe d config_FCC/Zprime_ll/cms/Zprime_mumu_"$ene"TeV.config
    ./myFit.exe p config_FCC/Zprime_ll/cms/Zprime_mumu_"$ene"TeV.config
    ./myFit.exe l config_FCC/Zprime_ll/cms/Zprime_mumu_"$ene"TeV.config

done

