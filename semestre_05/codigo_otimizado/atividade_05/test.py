import os, math, subprocess

# python3 test.py

qtd_repeticoes  = 10
media_caso_base = 0 # Salva a media do caso base flag == ' ' para usar em outras computacoes
contador = 0
flags = [
    ' ',
    '-ftree-vectorize',
    '-D INTRINSIC']

def exec_profile(flag):
    global media_caso_base
    global contador
    # Compilando com a flag
    os.system('g++ sum.c -msse3 -o exec {}'.format(flag))

    # Executano os testes e tirando a média dos valores
    for i in range(0, qtd_repeticoes):
        os.system("sudo perf stat -o Results/cache_{}.out -e cache-references,cache-misses ./exec".format(contador))
        os.system("sudo perf stat -o Results/branc_{}.out -e branches,branch-misses        ./exec".format(contador))
        contador += 1
        
    return 1

if __name__ == '__main__':
    print("[+] Iniciando Experimentos de Profilling ({} repetições/configuração)...".format(qtd_repeticoes))
    for flag in flags:
        print("[+] Configuração com a flag [{}]".format(flag))
        exec_profile(flag)
        print("[+] | -- Configuração com a flag [{}] finalizada.".format(flag))
    print("[+] Experimentos finalizados com SUCESSO.")
    print("[+] | -- Resultados finais salvos em resultados.csv")
