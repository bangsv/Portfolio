import pandas as pd
from sklearn.preprocessing import LabelEncoder
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression

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
X_train, X_test, y_math_train, y_math_test, y_reading_train, y_reading_test, y_writing_train, y_writing_test = train_test_split(
    X, y_math, y_reading, y_writing, test_size=0.3, random_state=42)

# обучение модели линейной регрессии для предсказания результатов математического экзамена
model_math = LinearRegression()
model_math.fit(X_train, y_math_train)

# обучение модели линейной регрессии для предсказания результатов чтения
model_reading = LinearRegression()
model_reading.fit(X_train, y_reading_train)

# обучение модели линейной регрессии для предсказания результатов письма
model_writing = LinearRegression()
model_writing.fit(X_train, y_writing_train)
print(model_writing.coef_)

# Вычислите R-квадрат для каждого предсказания
print('R-квадрат для предсказания результатов математического экзамена:', model_math.score(X_test, y_math_test))
print('R-квадрат для предсказания результатов чтения:', model_reading.score(X_test, y_reading_test))
print('R-квадрат для предсказания результатов письма:', model_writing.score(X_test, y_writing_test))

# Предскажите результаты тестовой выборки
y_math_pred = model_math.predict(X_test)
y_reading_pred = model_reading.predict(X_test)
y_writing_pred = model_writing.predict(X_test)

# Постройте датафрейм с предсказанными и фактическими значениями
df_pred = pd.DataFrame({'math score': y_math_test, 'math score predicted': y_math_pred,
                        'reading score': y_reading_test, 'reading score predicted': y_reading_pred,
                        'writing score': y_writing_test, 'writing score predicted': y_writing_pred})
#print(df_pred.head(10))
