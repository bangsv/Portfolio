from dsmltf  import *
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from pprint import pprint
from sklearn.decomposition import PCA

def scaling(df):
    df_scaled = df.copy()
    for col in df_scaled.columns:
        df_scaled[col] = (df_scaled[col] - df_scaled[col].mean()) / df_scaled[col].std()
    return df_scaled

df = pd.read_csv('wine-clustering.csv')
df = df.drop('Proline', axis=1)
#print(df.head())

df_pca = PCA(n_components=2).fit_transform(df)

df_pca = pd.DataFrame(df_pca, columns=['x', 'y'])
df_pca.head()

df_scaled = scaling(df_pca)
df_labels = ['' for i in range(len(df_pca))]
df_scaled.head()

prepared_data = df_scaled.values.tolist()
pprint(prepared_data[:5])

k = 4
km = KMeans(k)
km.train(prepared_data)
result = {}

for i in range(k):
    result[i] = []
for i in prepared_data:
    result[km.classify(i)].append(i)

pprint(result)

plt.figure(figsize=(10, 10))
sns.kdeplot(x=[i[0] for i in result[0]], y=[i[1] for i in result[0]], \
    color='red', fill=True, alpha=.5, thresh=0.2, levels=1000)
sns.kdeplot(x=[i[0] for i in result[1]], y=[i[1] for i in result[1]], \
    color='blue', fill=True, alpha=.5, thresh=0.2, levels=1000)
sns.kdeplot(x=[i[0] for i in result[2]], y=[i[1] for i in result[2]], \
    color='green', fill=True, alpha=.5, thresh=0.2, levels=1000)
sns.kdeplot(x=[i[0] for i in result[3]], y=[i[1] for i in result[3]], \
    color='#CC6000', fill=True, alpha=.5, thresh=0.2, levels=1000)
sns.kdeplot(x=[i[0] for i in result[4]], y=[i[1] for i in result[4]], \
    color='black', fill=True, alpha=.5, thresh=0.2, levels=1000)
sns.kdeplot(x=[i[0] for i in result[5]], y=[i[1] for i in result[5]], \
    color='purple', fill=True, alpha=.5, thresh=0.2, levels=1000)
sns.scatterplot(x=[i[0] for i in result[0]], y=[i[1] for i in result[0]], \
    color='red', label='Type 0')
sns.scatterplot(x=[i[0] for i in result[1]], y=[i[1] for i in result[1]], \
    color='blue', label='Type 1')
sns.scatterplot(x=[i[0] for i in result[2]], y=[i[1] for i in result[2]], \
    color='green', label='Type 2')
sns.scatterplot(x=[i[0] for i in result[3]], y=[i[1] for i in result[3]], \
    color='#CC6000', label='Type 3')
sns.scatterplot(x=[i[0] for i in result[4]], y=[i[1] for i in result[4]], \
    color='black', label='Type 4')
sns.scatterplot(x=[i[0] for i in result[5]], y=[i[1] for i in result[5]], \
    color='purple', label='Type 5')
plt.show()