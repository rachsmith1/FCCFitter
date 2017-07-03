for ene in 5 10 15 20 25 30 35 40;
do

    ./myFit.exe h config_Zprime_ll/Zprime_ll_"$ene"TeV.config
    ./myFit.exe w config_Zprime_ll/Zprime_ll_"$ene"TeV.config
    ./myFit.exe f config_Zprime_ll/Zprime_ll_"$ene"TeV.config
    ./myFit.exe d config_Zprime_ll/Zprime_ll_"$ene"TeV.config
    ./myFit.exe p config_Zprime_ll/Zprime_ll_"$ene"TeV.config
    ./myFit.exe l config_Zprime_ll/Zprime_ll_"$ene"TeV.config
    #./myFit.exe s config_Zprime_ll/Zprime_ee_"$ene"TeV.config

    #mv Zprime_ee_"$ene"TeV Outputs/Zprime/ee/

done

