import pandas as pd
from sklearn.preprocessing import LabelEncoder
import numpy as np
from dsmltf import *

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

def mean_squared_error(y_true, y_pred):
    """Вычисляет среднеквадратичную ошибку между y_true и y_pred."""
    return np.mean((y_true - y_pred) ** 2)

class LinearRegression:
    def __init__(self):
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

    def score(self, X, y):
        """Вычисляет R-квадрат между y_true и y_pred."""
        return 1 - mean_squared_error(y, self.predict(X)) / np.var(y)

# загрузка данных из csv-файла
df = pd.read_csv('exams_exams.csv')

# инициализация объекта LabelEncoder
le = LabelEncoder()

# преобразование категориальных признаков в числовые
df['gender'] = le.fit_transform(df['gender'])
df['race/ethnicity'] = le.fit_transform(df['race/ethnicity'])
df['parental level of education'] = le.fit_transform(df['parental level of education'])
df['lunch'] = le.fit_transform(df['lunch'])
df['test preparation course'] = le.fit_transform(df['test preparation course'])

# сохранение числового датасета в csv-файл
#df.to_csv('students_numeric.csv', index=False)

# загрузка данных из csv-файла
df = pd.read_csv('students_numeric.csv')

# разделение на признаки и целевую переменную
X = df.drop(['math score', 'reading score', 'writing score'], axis=1)
y_math = df['math score']
y_reading = df['reading score']
y_writing = df['writing score']

# разделение на обучающую и тестовую выборки
X_train_math, X_test_math, y_math_train, y_math_test = train_test_split(X.values, y_math, 0.3)
X_train_reading, X_test_reading, y_reading_train, y_reading_test = train_test_split(X.values, y_reading, 0.3)
X_train_writing, X_test_writing, y_writing_train, y_writing_test = train_test_split(X.values, y_writing, 0.3)

# обучение модели линейной регрессии для предсказания результатов математического экзамена
model_math = LinearRegression().fit(np.array(X_train_math), np.array(y_math_train))

# обучение модели линейной регрессии для предсказания результатов чтения
model_reading = LinearRegression().fit(np.array(X_train_reading), np.array(y_reading_train))

# обучение модели линейной регрессии для предсказания результатов письма
model_writing = LinearRegression().fit(np.array(X_train_writing), np.array(y_writing_train))

# Вычислите R-квадрат для каждого предсказания
print('R-квадрат для предсказания результатов математического экзамена:', model_math.score(X_test_math, y_math_test))
print('R-квадрат для предсказания результатов чтения:', model_reading.score(X_test_reading, y_reading_test))
print('R-квадрат для предсказания результатов письма:', model_writing.score(X_test_writing, y_writing_test))

#Предскажите результаты тестовой выборки
y_math_pred = np.array(model_math.predict(X_test_math))
y_reading_pred =np.array(model_reading.predict(X_test_reading))
y_writing_pred = np.array(model_writing.predict(X_test_writing))

#Постройте датафрейм с предсказанными и фактическими значениями

df_pred_math = pd.DataFrame({'math score': y_math_test, 'math score predicted': y_math_pred})
df_pred_reading = pd.DataFrame({'reading score': y_reading_test, 'reading score predicted': y_reading_pred})
df_pred_writing = pd.DataFrame({'writing score': y_writing_test, 'writing score predicted': y_writing_pred})

#Выведите первые 5 строк датафрейма
print("Math:\n",df_pred_math.head())
print("Read:\n",df_pred_reading.head())
print("Write:\n",df_pred_writing.head())
