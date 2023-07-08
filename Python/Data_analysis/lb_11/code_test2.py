import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression

df = pd.read_csv('exams_exams.csv')
df = pd.get_dummies(df, columns=['gender', 'race/ethnicity', 'parental level of education', 'lunch', 'test preparation course'])

X = df.drop(['math score', 'reading score', 'writing score'], axis=1)
y_math = df['math score']
y_reading = df['reading score']
y_writing = df['writing score']

X_train, X_test, y_math_train, y_math_test, y_reading_train, y_reading_test, y_writing_train, y_writing_test = train_test_split(X, y_math, y_reading, y_writing, test_size=0.3, random_state=42)

# Модель для предсказания math score
linreg_math = LinearRegression()
linreg_math.fit(X_train, y_math_train)

# Модель для предсказания reading score
linreg_reading = LinearRegression()
linreg_reading.fit(X_train, y_reading_train)

# Модель для предсказания writing score
linreg_writing = LinearRegression()
linreg_writing.fit(X_train, y_writing_train)

# R-квадрат для предсказания math score
print('R-квадрат для math score:', linreg_math.score(X_test, y_math_test))

# R-квадрат для предсказания reading score
print('R-квадрат для reading score:', linreg_reading.score(X_test, y_reading_test))

# R-квадрат для предсказания writing score
print('R-квадрат для writing score:', linreg_writing.score(X_test, y_writing_test))
