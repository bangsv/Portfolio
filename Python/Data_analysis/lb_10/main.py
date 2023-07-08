import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns
from dsmltf import *
from sklearn.decomposition import PCA

def main():

    df = pd.read_csv('Iris.csv')
    df_data = df.iloc[:, 1:5]
    print(df_data)
    df_labels = df.iloc[:, 5]
    print(df_labels)

    prepared_data = list(zip(df_data.values.tolist(), df_labels.values))
    k_main = k_classify(150, prepared_data)
    print(k_main)

    # Plot KNN
    grafic_KNN(k_main)

    df_mean = de_mean_matrix(df_data.values.tolist())
    #pca2 = principal_components(df_mean, 2)
    pca2 = PCA(n_components=2).fit_transform(df_mean).tolist()
    prepared_data_pca2 = list(tuple(zip(pca2, df_labels)))
    print(prepared_data_pca2)

    # Plot PCA (4->2)
    grafic_PCA(prepared_data_pca2)

    k_res = k_classify(150, prepared_data_pca2)
    grafic_PCA_KNA(k_res)

    print(df_data)
    df_int = intify(df_data, 10)
    print(df_int)

    gs2, gs2_powers = compress_general_serialization(pd.DataFrame(list(df_int)))
    prepared_data_gs2 = list(tuple(zip(gs2.values.tolist(), df_labels)))
    print(prepared_data_gs2)

    # Plot GS (4->2)
    grafic_GS(prepared_data_gs2)

    k_res_gs2 = k_classify(150, prepared_data_gs2)
    print(k_res_gs2)

    # Plot KNN (GS 4->2)
    grafic_GS_KNN(k_res_gs2)

    return 0

def k_classify(k, data):
    result = {}
    for k_1 in range(1, k + 1):
        n_correct = 0
        for item in data:
            values, actual_br = item
            other_items = [other_item for other_item in data \
                if other_item != item]
            predicted_br = knn_classify(k_1, other_items, values)
            if predicted_br == actual_br:
                n_correct += 1
        result[k_1] = (n_correct, len(data))
    return result

def compress_general_serialization(df):
    powers = [df[i].max()+1 for i in range(len(df.columns))]
    new_df = pd.DataFrame()
    _i = 0
    for i in range(0, len(df.columns), 2):
        new_df[_i] = df[i] + df[i+1] * powers[i]
        _i += 1
    if len(df.columns) % 2 == 1:
        new_df[_i] = df[len(df.columns) - 1]
        _i += 1
    return new_df, powers

def intify(df, multiplier=1):
    features =  [[nd[i] for nd in df.values.tolist()] \
        for i,_ in enumerate(df.columns)]
    minmax = [(min(f), max(f)) for f in features]
    ndata = [[round((ndi-minmax[i][0]), 5) for i,ndi \
        in enumerate(nd)] for nd in df.values.tolist()]
    return [[int(ndi*multiplier) for ndi in nd] for nd in ndata]

def grafic_KNN(k_main):
    # Plot KNN
    plt.figure(figsize=(7, 7))
    plt.title('KNN')
    plt.grid()
    plt.plot(k_main.keys(), [item[0]/item[1] for item in k_main.values()])
    plt.xlabel('k')
    plt.ylabel('Accuracy')
    plt.show()

def grafic_PCA(prepared_data_pca2):
    plt.figure(figsize=(7, 7))
    plt.title('PCA (4->2)')
    plt.grid()
    x_se = [item[0][0] for item in \
        prepared_data_pca2 if item[1] == 'Iris-setosa']
    y_se = [item[0][1] for item in \
        prepared_data_pca2 if item[1] == 'Iris-setosa']
    x_ve = [item[0][0] for item in \
        prepared_data_pca2 if item[1] == 'Iris-versicolor']
    y_ve = [item[0][1] for item in \
        prepared_data_pca2 if item[1] == 'Iris-versicolor']
    x_vi = [item[0][0] for item in \
        prepared_data_pca2 if item[1] == 'Iris-virginica']
    y_vi = [item[0][1] for item in \
        prepared_data_pca2 if item[1] == 'Iris-virginica']
    sns.scatterplot(x=x_se, y=y_se, color='red', label='Iris-setosa')
    sns.scatterplot(x=x_ve, y=y_ve, color='green', label='Iris-versicolor')
    sns.scatterplot(x=x_vi, y=y_vi, color='blue', label='Iris-virginica')
    plt.xlabel('PC1')
    plt.ylabel('PC2')
    plt.show()

def grafic_PCA_KNA(k_res):
    print(k_res)
    # Plot KNN (PCA 4->2)
    plt.figure(figsize=(7, 7))
    plt.title('KNN (PCA 4->2)')
    plt.grid()
    plt.plot(k_res.keys(), [item[0] / item[1] for item in k_res.values()],
        color='#ff5500')
    plt.xlabel('k')
    plt.ylabel('Accuracy')
    plt.show()

def grafic_GS(prepared_data_gs2):
    plt.figure(figsize=(7, 7))
    plt.title('GS (4->2)')
    plt.grid()
    i_se = [item[0][0] for item \
        in prepared_data_gs2 if item[1] == 'Iris-setosa']
    i_se = [item[0][1] for item \
        in prepared_data_gs2 if item[1] == 'Iris-setosa']
    i_ve = [item[0][0] for item \
        in prepared_data_gs2 if item[1] == 'Iris-versicolor']
    i_ve = [item[0][1] for item \
        in prepared_data_gs2 if item[1] == 'Iris-versicolor']
    i_vi = [item[0][0] for item \
        in prepared_data_gs2 if item[1] == 'Iris-virginica']
    i_vi = [item[0][1] for item \
        in prepared_data_gs2 if item[1] == 'Iris-virginica']
    sns.scatterplot(x=i_se, y=i_ve, color='red', \
        label='Iris-setosa', alpha=0.5, marker='o')
    sns.scatterplot(x=i_ve, y=i_vi, color='green', \
        label='Iris-versicolor', alpha=0.5, marker='o')
    sns.scatterplot(x=i_vi, y=i_se, color='blue', \
        label='Iris-virginica', alpha=0.5, marker='o')
    plt.xlabel('Sepal Size')
    plt.ylabel('Petal Size')
    plt.show()

def grafic_GS_KNN(k_res_gs2):
    plt.figure(figsize=(7, 7))
    plt.title('KNN (GS 4->2)')
    plt.grid()
    plt.plot(k_res_gs2.keys(), [item[0] / item[1] for item in k_res_gs2.values()],
        color='#22aa22')
    plt.xlabel('k')
    plt.ylabel('Accuracy')
    plt.show()

main()