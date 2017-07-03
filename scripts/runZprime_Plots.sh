python/limitplot.py -f "Outputs/fcc_v01/Zprime/ee/Zprime_ee_*/Limits/*" -c "Outputs/cms/Zprime/ee/Zprime_ee_*/Limits/*" -n "Zprime_ee_fcc_cms" -p "Z\' \rightarrow ee"
python/limitplot.py -f "Outputs/fcc_v01/Zprime/mumu/Zprime_mumu_*/Limits/*" -c "Outputs/cms/Zprime/mumu/Zprime_mumu_*/Limits/*" -n "Zprime_mumu_fcc_cms" -p "Z\' \rightarrow \mu\mu"

python python/limitplot.py -f "Outputs/fcc_v01/Zprime/ee/Zprime_ee_*TeV/Limits/*" -n "Zprime_ee_fcc_v01" -p "Z\' \rightarrow ee"
python python/limitplot.py -f "Outputs/fcc_v01/Zprime/mumu/Zprime_mumu_*TeV/Limits/*" -n "Zprime_mumu_fcc_v01" -p "Z\' \rightarrow \mu\mu"

python python/limitplot.py -f "Outputs/cms/Zprime/ee/Zprime_ee_*TeV/Limits/*" -n "Zprime_ee_cms" -p "Z\' \rightarrow ee"
python python/limitplot.py -f "Outputs/cms/Zprime/mumu/Zprime_mumu_*TeV/Limits/*" -n "Zprime_mumu_cms" -p "Z\' \rightarrow \mu\mu"

#python limitplot.py -f "Zprime_ll_*TeV/Limits/*" -n "Zprime_ll_fcc_v01" -p "Z\' \rightarrow ll"