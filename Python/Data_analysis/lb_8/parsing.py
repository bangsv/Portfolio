import requests, fake_useragent
from bs4 import BeautifulSoup 
import re 
import pandas as pd
import matplotlib.pyplot as plt 
from dsmltf import * 


# Делаем запросы с разными User-Agent
user = fake_useragent.UserAgent().random 
# Заголовки
headers = {'User-Agent': user}

# Парсинг стран 1.5.2 
def pars_2(url):
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

dataFrame = createDataFrame(pars_2('https://www.worldometers.info/world-population/uganda-population/'))

print(dataFrame['Year'][:18])