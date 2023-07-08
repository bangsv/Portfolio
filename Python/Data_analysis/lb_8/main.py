import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from bs4 import BeautifulSoup
import requests, fake_useragent
import re
from dsmltf import *

# Делаем запросы с разными User-Agent
user = fake_useragent.UserAgent().random 
# Заголовки
headers = {'User-Agent': user}

def pars(url):
    # Создаем сессию для запроса
    request_session = requests.Session()
    # Делаем запрос
    request = request_session.get(url, headers=headers)
    # Проверяем статус запроса
    if request.status_code == 200:
        # Создаем объект BeautifulSoup для парсинга
        soup = BeautifulSoup(request.content, 'lxml') # lxml - парсер

        new_data = str(soup.find_all('div', class_='table-responsive'))
    
    rows = re.findall(r'<tr>(.*?)</tr>', new_data, re.DOTALL)
    data = []
    for row in rows:
        elements = re.findall(r'<td>(.*?)</td>', row)
        data.append(elements)
    
    for row in data:
        for i, val in enumerate(row):
            row[i] = re.sub('<.*?>', '', val) # Remove all tags
    one_data = []

    for x in data:
        one_data.extend(x if isinstance(x, list) else [x] )

    n_cols = 13
    result = [one_data[i:i+n_cols] for i in range(0, len(one_data), n_cols)]
    
    for row in result:
        for i in range(len(row)):
            row[i] = row[i].replace('%', '').replace('\xa0', '')

    return result

def createDataFrame(data):
    df = pd.DataFrame(data, columns=['Year', 'Population', 'Yearly %', 'Yearly Change', 'Migrants (net)', 'Median Age', 'Fertility Rate', 'Density (P/Km²)', 'Urban Pop %', 'Urban Population', 'Countrys Share of World Pop', 'World Population', 'Uganda'])
    df = df.drop_duplicates(subset=['Year'])
    df = df.sort_values(by='Year')
    # создание объекта модели
    df["Year"] = df["Year"].astype(int)
    df["Median Age"] = df["Median Age"].astype(float)
    df["Fertility Rate"] = df["Fertility Rate"].astype(float)
    df['Migrants (net)'] = df["Migrants (net)"].replace("", "0", regex=True).replace(",", ".", regex=True).astype(float)
    
    return df

class LinearRegression:
    def init(self):
        self.coef_ = None
        self.intercept_ = None
    
    def fit(self, X, y):
        if not isinstance(X, np.ndarray):
            X = X.to_numpy().astype(float)
        if not isinstance(y, np.ndarray):
            y = y.to_numpy().astype(float)
        # Добавляем столбец из единиц для свободного коэффициента
        X = np.insert(X, 0, 1, axis=1)
        # Решаем уравнение X.T * X * w = X.T * y для w
        self.coef_ = inv(X.T @ X) @ X.T @ y 
        # Сохраняем свободный коэффициент
        self.intercept_ = self.coef_[0]
        # Удаляем свободный коэффициент из вектора коэффициентов
        self.coef_ = self.coef_[1:]
        return self
    
    def predict(self, X):
        # Добавляем столбец из единиц для свободного коэффициента
        X = np.insert(X, 0, 1, axis=1)
        # Вычисляем предсказание
        return X @ np.insert(self.coef_, 0, self.intercept_)

def shape(data):
    return len(data), len(data[0])

# Вычисление обратной матрицы методом Гаусса с выбором главного элемента по столбцу (поиск максимального элемента в столбце)
# и перестановкой строк для лучшего числа обусловленности (поиск максимального элемента в столбце) 
def inv(A):
    """Вычисляет обратную матрицу"""
    n = shape(A)[0]
    A = np.hstack((A, np.eye(n)))
    for i in range(n):
        # Поиск максимального элемента в столбце
        max_el = abs(A[i, i])
        max_row = i
        for k in range(i+1, n):
            if abs(A[k, i]) > max_el:
                max_el = abs(A[k, i])
                max_row = k
        # Перестановка строк для лучшего числа обусловленности
        if max_row != i:
            A[[i, max_row]] = A[[max_row, i]]
        # Делаем диагональный элемент равным 1
        A[i] = A[i] / A[i, i]
        for j in range(n):
            if i != j:
                A[j] = A[j] - A[j, i]*A[i]
    return A[:, n:]

def plot_year_med_age(original_series, approximated_series):
    plt.figure(figsize=(10, 5))
    plt.plot(approximated_series.index, approximated_series.values, \
        label='Approx', color='#ff0000')
    plt.plot(original_series.index, original_series.values, \
        label='Original', color='#00aaff')    
    plt.xlabel('Year')
    plt.ylabel('Median Age')
    plt.title('Median Age by Year')
    plt.legend()
    plt.show()

# Задание 1
data = createDataFrame(pars('https://www.worldometers.info/world-population/france-population/'))
print("Задание 1")
print(data)

# Задание 2
print("Задание 2")
series = pd.Series(data['Median Age'].values, index = data['Year'].values)
print(series)

# Задание 3
print("Задание 3")
a_mig, b_mig = least_squares_fit(data['Year'].values[:18], 
    data['Migrants (net)'].values[:18])
print('a, b =', a_mig, b_mig)
plt.title('Migrants (net)')
plt.plot(data['Year'].values, data['Migrants (net)'].values, 'o')
plt.plot(data['Year'].values, b_mig * data['Year'].values + a_mig, '--', \
    color='#ffaaaa')     
plt.plot(data['Year'].values[:18], b_mig * data['Year'].values[:18] + a_mig)
plt.show()

a_fert, b_fert = least_squares_fit(data['Year'].values[:18], \
    data['Fertility Rate'].values[:18])
#print('a, b =', a_fert, b_fert)
# plt.title('Fertility Rate')
# plt.plot(data['Year'].values, data['Fertility Rate'].values, 'o')
# plt.plot(data['Year'].values, b_fert * data['Year'].values + a_fert, '--', \
#     color='#ffaaaa')
# plt.plot(data['Year'].values[:18], b_fert * data['Year'].values[:18] + a_fert)
# plt.show()

a_age, b_age = least_squares_fit(data['Year'].values[:18], \
    data['Median Age'].values[:18])
# print('a, b =', a_age, b_age)
# plt.title('Median Age')
# plt.plot(data['Year'].values, data['Median Age'].values, 'o')
# plt.plot(data['Year'].values, b_age * data['Year'].values + a_age, '--', \
#     color='#ffaaaa')
# plt.plot(data['Year'].values[:18], b_age * data['Year'].values[:18] + a_age)
# plt.show()

y_mig = predict(a_mig, b_mig, 2020)
y_fert = predict(a_fert, b_fert,2020)
y_age = predict(a_age, b_age, 2020)
#print(y_mig, y_fert, y_age) # 
 
# рассчитываем линейные тренды
x = data['Year'].values.reshape(-1, 1)
y1 = data['Median Age'].values.reshape(-1, 1)
y2 = data['Fertility Rate'].values.reshape(-1, 1)
y3 = data['Migrants (net)'].values.reshape(-1, 1)

model1 = LinearRegression().fit(x, y1)
model2 = LinearRegression().fit(x, y2)
model3 = LinearRegression().fit(x, y3)

# рассчитываем значения для 2020 года
x_new = [[2020]]
y1_new = model1.predict(x_new)[0]
y2_new = model2.predict(x_new)[0]
y3_new = model3.predict(x_new)[0]

# строим модель связи
X = data[['Fertility Rate', 'Migrants (net)']]
y = data['Median Age']

model = LinearRegression().fit(X, y)


FR = 1.5 
M = 1000
median_age = model.predict([[FR, M]])[0]

print("Fertility Rate: ", FR)
print("Migrants (net): ", M)
print("Median age: ", round(median_age, 3))

cereal_prev = pd.Series(data['Median Age'].values, \
    index=data['Year'].values)[:18]

years = data['Year'].values[18:]
for year in years:
    cereal_prev[year] = model.predict([[predict(a_fert, b_fert, year), \
        predict(a_mig, b_mig, year)]])[0]

plot_year_med_age(series, cereal_prev)

