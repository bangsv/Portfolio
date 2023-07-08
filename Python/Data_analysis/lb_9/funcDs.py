# 1. Выберите датасет на kaggle.com с не менее, чем 6 признаками 
# (не считая метки)
# 2. Проведите предобработку, после которой все данные должны быть векторами с 
# целочисленными координатами, лежащими в 
# заданном вами диапазоне.
# 3. Снизьте размерность данных на 2, используя метод главных компонент. 
# Интерпретируйте полученные признаки данных.
# 4. Снизьте размерность предобработанных данных на 2, используя сериализацию. 
# Интерпретируйте полученные признаки данных.
# 5. Постройте точечные диаграммы данных сниженной размерности (два комплекта 
# диаграмм). Вывод диаграмм должен производиться по запросу пользователя 
# (пользователь указывает оси-признаки).

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from dsmltf import *
import seaborn as sns
from sklearn.preprocessing import MinMaxScaler

def grafic_PCA(pca):
    plt.figure(figsize=(10, 10))
    sns.scatterplot(x=[item[0] for item in pca], \
        y=[item[1] for item in pca], \
            alpha=0.5, marker='x', color='#cc4040')
    sns.scatterplot(x=[item[1] for item in pca], \
        y=[item[0] for item in pca], \
            alpha=0.5, marker='x', color='#40cc40')
    plt.xlabel('PC#1')
    plt.ylabel('PC#2')
    plt.title('PCA')
    plt.show()

def get_data():
    temp = pd.read_csv('housing.csv')
    temp.drop(columns=['ocean_proximity'], inplace=True)
    temp.fillna(0, inplace=True)

    # normalize the data
    scaler = MinMaxScaler()
    normalized_data = scaler.fit_transform(temp).astype(float)

    name = ['longitude', 'latitude', 'housing_median_age', 'total_rooms','total_bedrooms', 'population','households', 'median_income', 'median_house_value']
    scaled_df = pd.DataFrame(normalized_data, columns=name)
    return scaled_df[:100]

def intify(df):
    features =  [[nd[i] for nd in df.values.tolist()] for i,_ in enumerate(df.columns)]
    minmax = [(min(f), max(f)) for f in features]
    ndata = [[round((ndi-minmax[i][0]), 5) for i,ndi in enumerate(nd)] for nd in df.values.tolist()]
    return [[int(ndi*10000) for ndi in nd] for nd in ndata]

def compress_general_serialization(df):
    powers = [df[i].max()+1 for i in range(len(df.columns))]
    #print('powers:', powers)
    new_df = pd.DataFrame()
    _i = 0
    for i in range(0, len(df.columns)-1, 2): # exclude the last index if odd number of columns
        new_df[_i] = df[i] + df[i+1] * powers[i]
        _i += 1
    if len(df.columns) % 2 == 1:
        new_df[_i] = df[len(df.columns) - 1]
        _i += 1
    return new_df, powers

def disassemble_general_serialization(df, powers):
    new_df = pd.DataFrame()
    _i = 0
    for i in range(0, len(df.columns)):
        new_df[_i] = df[i] % powers[_i]   
        new_df[_i+1] = df[i] // powers[_i]   
        _i += 2
    return new_df

def grafic_DGS(gen):
    plt.figure(figsize=(10, 10))
    sns.scatterplot(x=[item[2] for item in gen.values.tolist()], \
        y=[item[3] for item in gen.values.tolist()], \
            alpha=0.5, marker='x', color='#cc4040')
    sns.scatterplot(x=[item[1] for item in gen.values.tolist()], \
        y=[item[2] for item in gen.values.tolist()], \
            alpha=0.5, marker='x', color='#40cc40')

    plt.xlabel('GS#1')
    plt.ylabel('GS#2')
    plt.title('General Serialization')
    plt.show()

def main():

    # Получаем данные из файла 
    df = get_data()
    # Среднее значение по столбцам 
    df_mean = de_mean_matrix(df.values.tolist())
    pca = principal_components(df_mean, 2)
   
    grafic_PCA(pca)
    int_data = intify(df)
    gen, powers = compress_general_serialization(pd.DataFrame(list(int_data)))
    gen.values.tolist()
    disassemble_general_serialization(gen, powers)
    grafic_DGS(gen)

main()
