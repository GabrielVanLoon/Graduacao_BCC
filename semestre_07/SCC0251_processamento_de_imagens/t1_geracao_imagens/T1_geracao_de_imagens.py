#!/usr/bin/env python
# coding: utf-8

# # Trabalho 1 - Geração de Images 
# 
# - Disciplina: SCC0251 - Processamento de Imagens 
# - Prof. Lizeth Andrea Castellanos Beltran
# - Autor: Gabriel Van Loon Bode da Costa (10391607)
# - Data: abril/2021
# 
# ### Objetivo do Trabalho
# 
# Utilizar funções matemáticas para a geração de imagens com o objetivo de familizar o uso das ferramentas e reforçar o conceito de amostragem de imagens. O programa irá primeiro criar uma imagem sintética por meios de uma das 5 funções pré-definidas e em seguida simular o processo de amostragem sobre a mesma.

import imageio as img
import numpy as np
import random
import math


# ### 1ª Etapa - Leitura dos Parâmetros
# 
# O programa recebe como entrada 7 parâmetros: o nome da imagem de referencia (`R`), o tamanho da imagem sintetizada (`C`), a função gerador (`F = {1,...,5}`), o parâmetro `Q` usado em algumas das funções, o tamanho lateral da imagem amostrada (`N`), o número de bits por pixel (`B = {1,...,8}`) e a semente inicial para os valores aleatórios (`S`).


# Caso de teste 1: R=ex1.npy C=512 F=1 Q=2 N=256 B=4 S=1
# Caso de teste 2: R=ex2.npy C=512 F=2 Q=32 N=256 B=6 S=1
# Caso de teste 3: R=ex3.npy C=512 F=3 Q=1001 N=256 B=3 S=1
# Caso de teste 4: R=ex4.npy C=512 F=4 Q=1 N=256 B=3 S=13
# Caso de teste 5: R=ex5.npy C=512 F=5 Q=1 N=256 B=8 S=6666

R = input().rstrip()
C = int(input().rstrip())
F = int(input().rstrip())
Q = int(input().rstrip())
N = int(input().rstrip())
B = int(input().rstrip())
S = int(input().rstrip()) 


# Iniciando a Semente Aleatória do programa
random.seed(S)


# ### 2ª Etapa - Definindo e Usando as Funções Geradoras
# 
# Nessa etapa iremos criar uma matriz de tamanho CxC utilzando uma das 5 funções geradoras definidas a seguir:

def generator1(image, Q=False):
    for x in range(0,len(image)):
        for y in range(0,len(image)):
            image[x,y] = x*y + 2*y

def generator2(image, Q=1.0):
    for x in range(0,len(image)):
        for y in range(0,len(image)):
            image[x,y] = np.abs(np.cos(x/Q) + 2*np.sin(y/Q))

def generator3(image, Q=1.0):
    for x in range(0,len(image)):
        for y in range(0,len(image)):
            image[x,y] = np.abs(3*(x/Q) - np.cbrt(y/Q))

def generator4(image, Q=False):
    for y in range(0,len(image)):
        for x in range(0,len(image)):
            image[x,y] = random.random()

def generator5(image, Q=False):
    x,y = (0,0)
    for step in range(1+C*C):
        image[x,y] = 1.0
        dx = random.randint(-1,1)
        dy = random.randint(-1,1)
        x,y = ((x+dx)%C, (y+dy)%C) 

# Encapsula todas as funcoes em um array de funcoes para ser utilizado em seguida
image_generators = [False, generator1, generator2, generator3, generator4, generator5]


# Generating the image
synth_image = np.zeros((C,C), dtype=float)
image_generators[F](synth_image, Q)


# ### 3ª Etapa - Amostragem da Imagem (Downsampling)
# 
# Como queremos gerar uma imagem de tamanho `N <= C` iremos dividir a imagem sintetizada em regiões de tamanho N² e utilizar um método simples de amostragem que escolhe sempre o primeiro elemento de cada região (Outras opções poderiam ser: pegar o valor médio, o máximo, o mínimo, ou aplicar alguma outra lógica)


sampled_image = np.zeros((N,N), dtype=float)

# Basic Downsampling
for x in range(0,len(sampled_image)):
    for y in range(0,len(sampled_image)):
        sampled_image[x,y] = synth_image[int((C/N))*x, int((C/N))*y]


# ### 4ª Etapa - Quantização
# 
# Nesta etapa iremos normalizar os valores obtidos até então para o intervalo `[0,255]`, para em seguida converter os dados para o tipo `uint8`. Em seguida iremos transforma os valore para que sejam representados por apenas `B` bits de informação.

# Normalize values from [min_pixel, max_pixel](float) to [0, 255](uint32)
norm_image = sampled_image - sampled_image.min()
norm_image = norm_image / norm_image.max()
norm_image = norm_image * 255.0
norm_image = norm_image.astype(np.uint8)


# Select the first B bits and remove the rest
norm_image = norm_image >> (8-B)
norm_image = norm_image << (8-B)


# ### Etapa Extra - Visualizando a imagem gerada
# 
# Para visualizarmos a imagem gerada podemos descomentar os trechos de código a seguir

# import matplotlib.pyplot as plt
# plt.imshow(norm_image, cmap='gray')
# plt.show()


# ### 5ª Etapa - Comparando com a Referência
# 
# No primeiro parâmetro lido recebemos o caminho da imagem de referência que deveria ser resultante do caso de teste. Nesta etapa vamos carregar essa imagem e calcular a Raiz do Erro Quadrático (RSE) para verificar quão próximo chegamos do resultado correto.

# Load reference image
reference_image = np.load(R)

# Visualize the reference image
# plt.imshow(reference_image, cmap='gray')
# plt.show()

# Calculating the error 
error = 0.0
for x in range(0,len(norm_image)):
    for y in range(0,len(norm_image)):
        error += (float(norm_image[x,y]-reference_image[x,y])) * (float(norm_image[x,y]-reference_image[x,y]))
error = np.sqrt(error)

# Printing the final error
print(format(error, ".4f"))

