import glob
import optparse
import subprocess
import sys
import ROOT as r
#__________________________________________________________
def scalelumi(cfg, lumi):
    with open(cfg) as f:
        infile = f.readlines()
        for line in xrange(len(infile)):
            if 'Lumi:' in infile[line] :
                infile[line]='  Lumi:%i\n'%lumi
            if 'LumiScale:' in infile[line] :
                infile[line]='  LumiScale:%i\n'%lumi

    with open(cfg.replace('.config','_signi.config'), "w") as f1:
        f1.writelines(infile) 



#__________________________________________________________
if __name__=="__main__":
    
    parser = optparse.OptionParser(description="analysis parser")
    parser.add_option('-f', '--file', dest='files', type=str, default='')

    ops, args = parser.parse_args()
    config_files=glob.glob(ops.files)
    
    config_files = [i for i in config_files if '~' not in i and 'signi' not in i]
    print config_files

    for cfg in config_files:
        scalelumi(cfg,10)

        cmd="./myFit.exe h %s"%(cfg.replace('.config','_signi.config'))
        p=subprocess.Popen(cmd, shell=True)
        p.communicate()
        cmd="./myFit.exe w %s"%(cfg.replace('.config','_signi.config'))
        p=subprocess.Popen(cmd, shell=True)
        p.communicate()
        cmd="./myFit.exe s %s"%(cfg.replace('.config','_signi.config'))
        p=subprocess.Popen(cmd, shell=True)
        p.communicate()


        signi = r.TFile.Open("Zprime_ee_5TeV/Significance/Zprime_ee_5TeV.root")
        histo = signi.Get("hypo")
        print '----------------------------',histo.GetBinContent(2)
        sys.exit(3)
