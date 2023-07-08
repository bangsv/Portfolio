import pandas as pd
import numpy as np
from sklearn.preprocessing import StandardScaler
from sklearn.decomposition import PCA
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.manifold import TSNE
from dsmltf import *
from sklearn.preprocessing import MinMaxScaler

def get_data():
    temp = pd.read_csv('housing.csv')
    temp.drop(columns=['ocean_proximity'], inplace=True)
    temp.fillna(0, inplace=True)

    # normalize the data
    scaler = MinMaxScaler()
    normalized_data = scaler.fit_transform(temp).astype(float)

    name = ['longitude', 'latitude', 'housing_median_age', 'total_rooms','total_bedrooms', 'population','households', 'median_income', 'median_house_value']
    scaled_df = pd.DataFrame(normalized_data, columns=name)
    return scaled_df

# Загрузка датасета
df = get_data()

# Удаление строк с пропущенными значениями
df.dropna(inplace=True)

# Приведение всех данных к целочисленному типу
df = df.astype(float)

print(df)

# Проводим масштабирование
scaler = StandardScaler()
data_scaled = scaler.fit_transform(df)

# Преобразуем данные в целочисленные значения
data_int = np.round(data_scaled).astype(int)
print(data_int)

print()

# Проводим PCA-преобразование
pca = PCA(n_components=2)
data_pca = pca.fit_transform(data_int)
print(data_pca)

# Интерпретируем полученные признаки
print("Первый главный компонент: ", pca.components_[0])
print("Второй главный компонент: ", pca.components_[1])

# Выполним сериализацию для снижения размерности на 2
#tsne = TSNE(n_components=2)
#X_tsne = tsne.fit_transform(data_int)

# Построение точечной диаграммы PCA
plt.figure(figsize=(10, 10))
sns.scatterplot(x=data_pca[:, 0], y=data_pca[:, 1],  alpha  = 0.5, marker='x', color = '#009900')
plt.xlabel('PC1')
plt.ylabel('PC2')
plt.title('PCA')
plt.show()
