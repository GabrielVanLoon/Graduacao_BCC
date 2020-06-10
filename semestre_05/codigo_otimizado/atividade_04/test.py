import os, math, subprocess
import numpy as np 
import pandas as pd
import matplotlib.pyplot as plt

# python3 test.py

qtd_repeticoes  = 3
media_caso_base = 0 # Salva a media do caso base flag == ' ' para usar em outras computacoes
flags = [
    ' ',
    '-O1',
    '-O2',
    '-O3',
    '-finline',
    '-fstrict-aliasing',
    '-ftree-pre',
    '-ftree-vrp',
    '-ftree-ch',
    '-freorder-functions',
    '-fcaller-saves',
    '-freorder-blocks',
    '-finline-small-functions',
    '-fomit-frame-pointer',
    '-fguess-branch-probality',
    '-fpartial-inlining',
    '-foptimize-sibling-calls',
    '-fdce',
    '-fpeephole2',
    '-fif-conversion',
    '-ftree-partial-pre']

def exec_profile(flag):
    global media_caso_base
    # Compilando com a flag
    os.system('g++ fannkuch-redux.cpp -o exec -march=x86-64 {}'.format(flag))

    # Executano os testes e tirando a média dos valores
    media = 0.0
    for i in range(0, qtd_repeticoes):
        proc = subprocess.Popen("./exec", stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
        _, stderr = proc.communicate()
        media += float(stderr.decode("utf-8")) 
    media = media/float(qtd_repeticoes)

    variacao = 0.0
    # Se esse for o caso base, salva na variavel global
    if flag == ' ':
        media_caso_base = media
    else:
        variacao = (media_caso_base - media)/media_caso_base 
    # Computa a melhoria em % baseado na mesma formula do paper

    # Salvando os resultados no arquivo de resultados
    if flag == ' ':
        fp = open('test_results.csv', 'w')
    else:
        fp = open('test_results.csv', 'a')
    
    fp.write("{};{:.6f};{:.6f}\n".format(flag,media,variacao));
    fp.close()
    return 1

if __name__ == '__main__':
    print("[+] Iniciando Experimentos de Profilling ({} repetições/configuração)...".format(qtd_repeticoes))
    for flag in flags:
        print("[+] Configuração com a flag [{}]".format(flag))
        exec_profile(flag)
        print("[+] | -- Configuração com a flag [{}] finalizada.".format(flag))
    print("[+] Experimentos finalizados com SUCESSO.")
    print("[+] | -- Resultados finais salvos em resultados.csv")
