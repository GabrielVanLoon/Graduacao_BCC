#!/usr/bin/env python
# coding: utf-8

# # Trabalho 2 - Realce e Superresoluçãi
# 
# - **Disciplina:** SCC0251 - Processamento de Imagens 
# - **Prof.** Moacir Antonelli Ponti
# - **Autor:** Gabriel Van Loon Bode da Costa (10391607)
# - **Data:** maio/2021
# 
# ### Objetivo do Trabalho
# 
# Utilizar técnicas de filtragem de imagens utilizando filtros 1D, 2D ou de mediana em diferentes imagens.

# In[1]:


import imageio as img
import numpy as np
import random
import math


# ### 1ª Etapa - Leitura dos Parâmetros
# 
# O programa recebe como entrada os parâmetros: o nome base da imagem a ser trabalhada (`I`), a identificação do método de filtragem executado (`F = {1, 2, 3}`), o tamanho do filtro (`N`), e os valores do filtro (`W[]`) se necessário

# In[2]:


# Caso de teste 1: I=image02_salted.png    F=3   N=3   W=[]
# caso de teste 2: I=airplane.png          F=2   N=3   W=[-1 -1 -1 -1 8 -1 -1 -1 -1]

I = input().rstrip()
F = int(input().rstrip())
N = int(input().rstrip())
W = []
PADSIZE = int((N-1)/2)


# In[3]:


if F == 1:
    W = np.array([int(x) for x in input().split()], dtype=int)
elif F == 2:
    W = np.array([ [int(x) for x in input().split()] for i in range(N)], dtype=int)


# Por fim vamos deixar carregada a imagem de input a ser utilizada nas próximas etapas

# In[4]:


input_image = img.imread(I).astype(np.float32)


# ### 2ª Etapa - Aplicando as Filtragems
# 
# A seguir teremos as 3 possiveis opções de filtragem que estão definidas em funções: 
# 
# - **Convolução 1D** (opção 1)
#     - Converter a imagem em um array de 1D
#     - Aplicar o **wrap** padding method
#     - aplicar o filtro W na imagem
#     - Retorna a imagem para 2D
# - **Convolução 2D** (opção 2)
#     - Aplicar o **reflection** padding method
#     - aplicar o filtro W na imagem
# - **Filtro de Mediana** (opção 3)
#     - Aplicar o **zero** padding method
#     - Aplicar o filtro de mediana

# In[5]:


def filtering_1D(original_image):
    # Turning image to 1D
    pad_img = original_image.copy().flatten()
    output  = np.zeros(pad_img.shape, dtype=np.float32)
    
    # Apply padding
    pad_img = np.pad(pad_img, PADSIZE, mode="wrap")
    
    # Apply 1D filter
    for i in range(PADSIZE, pad_img.shape[0]-PADSIZE):
        output[i-PADSIZE] = np.sum(np.multiply(W, pad_img[i-PADSIZE:i+PADSIZE+1]))
        
    # Return to 2D and return final result matrix
    return output.reshape(original_image.shape)


# In[6]:


def filtering_2D(original_image):
    pad_img = original_image.copy()
    output  = np.zeros(pad_img.shape, dtype=np.float32)
    
    # Apply padding
    pad_img = np.pad(pad_img, PADSIZE, mode="reflect")
    
    # Apply 2D filter
    for i in range(PADSIZE, pad_img.shape[0]-PADSIZE):
        for j in range(PADSIZE, pad_img.shape[1]-PADSIZE):
            output[i-PADSIZE,j-PADSIZE] = np.sum(np.multiply(W, pad_img[i-PADSIZE:i+PADSIZE+1,j-PADSIZE:j+PADSIZE+1]))
        
    # Return final result matrix
    return output


# In[7]:


def filtering_median(original_image):
    pad_img = original_image.copy()
    output  = np.zeros(pad_img.shape, dtype=np.float32)
    
    # Apply padding
    pad_img = np.pad(pad_img, PADSIZE, mode="constant")
    
    # Apply 2D filter
    for i in range(PADSIZE, pad_img.shape[0]-PADSIZE):
        for j in range(PADSIZE, pad_img.shape[1]-PADSIZE):
            output[i-PADSIZE,j-PADSIZE] = np.median(pad_img[i-PADSIZE:i+PADSIZE+1,j-PADSIZE:j+PADSIZE+1])
        
    # Return final result matrix
    return output


# Com os filtros definidos, podemos agora aplicar a opção selecionada e obter a imagem de output

# In[8]:


filters = [False, filtering_1D, filtering_2D, filtering_median]
output_image = filters[F](input_image)


# Por fim precisamos normalizar a imagem de output para o range \[0, 255\]

# In[9]:


output_image = output_image-np.min(output_image)
output_image = output_image/np.max(output_image)
output_image = output_image * 255.0


# ### 5ª Etapa - Comparando Entrada e Saída

# In[10]:


input_image  = input_image.astype(np.float32)
output_image = output_image.astype(np.float32)

# Calculating the error 
error =  np.sqrt(np.sum(np.power(input_image-output_image, 2.0))/output_image.size)
print(format(error, ".4f"))


# ### Etapa Extra - Visualizando as imagens geradas com a referência

# In[11]:


# import matplotlib.pyplot as plt

# plt.figure(figsize=(12,12)) 
# plt.subplot(121)
# plt.imshow(input_image, cmap="gray", vmin=0, vmax=255)
# plt.title("Input Image")
# plt.axis('off')
# plt.subplot(122)
# plt.imshow(output_image, cmap="gray", vmin=0, vmax=255)
# plt.title("Filtered image")
# plt.axis('off')

