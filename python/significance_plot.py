import json
import optparse
import sys
from matplotlib import pyplot as plt
import numpy as np
from scipy.interpolate import interp1d

#__________________________________________________________
def getMassDisco(signiDict):
    
    indict=None
    with open(signiDict,'r') as f:
        indict = json.load(f)
        
    mass =[]
    disco = []

    for m in indict:
        signi=[]
        lumi=[]
        print m
        for i in indict[m]:
            signi.append(i['signi'])
            lumi.append(i['lumi'])
        print signi
        print lumi

        signi,lumi = zip(*sorted(zip(signi, lumi)))

        plt.figure()
        xnew = np.linspace(min(lumi), max(lumi), 100)
        f = interp1d(lumi, signi)
        plt.plot(lumi, signi, 'o-', xnew, f(xnew), '-')
        plt.plot([min(lumi), max(lumi)], [5, 5], 'k-', lw=2)
        plt.plot([min(lumi), max(lumi)], [3, 3], 'k-', lw=2)            
        plt.xlabel('luminosity fb$^{-1}')
        plt.ylabel('significance sigma')
        plt.grid(True)
        plt.savefig('Signi_%s.eps'%(m,))
        plt.close()


        plt.figure()
        xnew = np.linspace(min(signi), max(signi), 1000)
        f = interp1d(signi, lumi)
        plt.plot(signi, lumi, 'o-', xnew, f(xnew), '-')
        plt.plot([5,5],[min(lumi), max(lumi)], 'k-', lw=2)
        plt.plot([3,3],[min(lumi), max(lumi)], 'k-', lw=2)            
        plt.ylabel('luminosity fb$^{-1}')
        plt.xlabel('significance sigma')
        plt.grid(True)
        discolumi = f(5) if xnew[-1]>5.0 else f(xnew[-1])
        plt.plot([0,5],[discolumi, discolumi], 'k-', lw=2)            
        plt.savefig('SigniInverse_%s.eps'%(m,))
        print 'lumi = %f'%discolumi
        plt.close()

        mass.append(int(m))
        disco.append(discolumi)

    Mass,Disco = zip(*sorted(zip(mass, disco)))
    print Mass
    print Disco
    return Disco,Mass

#__________________________________________________________
if __name__=="__main__":
    
    parser = optparse.OptionParser(description="analysis parser")
    parser.add_option('-f', '--files', dest='files', type=str, default='')
    parser.add_option('-n', '--names', dest='names', type=str, default='')
    parser.add_option('-p', '--plot', dest='plot', type=str, default='')

    ops, args = parser.parse_args()
    signiDict=ops.files
    names=ops.names

    signiList = signiDict.split(' ')
    namesList = names.split(' ')
    print signiList
    print namesList
    if len(signiList)!=len(namesList):
        print 'different length, name, signi, exit',len(signiList),'  ',len(namesList)
        sys.exit(3)
    plt.figure()
    
    for s in xrange(len(signiList)):
        print signiList[s]
        Disco,Mass=getMassDisco(signiList[s])
        Disco=[i/1000. for i in Disco]
        plt.plot(Mass, Disco, label=namesList[s])

    plt.ylabel('luminosity fb$^{-1}$')
    plt.xlabel('mass [TeV]')
    plt.title('luminosity verus mass for a 5 $\sigma$ discovery')
    plt.grid(True)
    plt.legend(loc=4)
    plt.yscale('log')
    plt.savefig('DiscoveryPotential_%s.eps'%(ops.plot))
    plt.close()




