#python python/significance.py -f "config_FCC/Zprime_ll_fcc_v01/Zprime_ee_*TeV.config" -n Zprime_ee_fcc_v01
#python python/significance.py -f "config_FCC/Zprime_ll_fcc_v01/Zprime_mumu_*TeV.config" -n Zprime_mumu_fcc_v01
#python python/significance.py -f "config_FCC/Zprime_ll_fcc_v01_combined/Zprime_ll_*TeV.config" -n Zprime_ll_fcc_v01 -c

#python python/significance.py -f "config_FCC/Zprime_ll_cms/Zprime_ee_*TeV.config" -n Zprime_ee_cms
python python/significance.py -f "config_FCC/Zprime_ll_cms/Zprime_mumu_*TeV.config" -n Zprime_mumu_cms
python python/significance.py -f "config_FCC/Zprime_ll_cms_combined/Zprime_ll_*TeV.config" -n Zprime_ll_cms -c

