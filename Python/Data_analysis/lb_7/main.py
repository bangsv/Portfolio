import requests, fake_useragent
from bs4 import BeautifulSoup 
from colorama import Fore, Back, Style
import re
import pandas as pd

import getcourse

# Делаем запросы с разными User-Agent
user = fake_useragent.UserAgent().random 
# Заголовки
headers = {'User-Agent': user}

def parsing(url):
    # Создаем сессию для запроса 
    request_session = requests.Session()
    # Делаем запрос
    request = request_session.get(url, headers=headers)
    # Проверяем статус запроса
    if request.status_code == 200:
        # Создаем объект BeautifulSoup для парсинга
        soup = BeautifulSoup(request.content,'lxml') 
        
        search_data = str(soup.find_all('div',class_ = 'teaser-line'))
        
        pattern = r'<div.*?class="teaser-line".*?>\s*<div.*?class="teaser-body".*?>\s*<h3>\s*<a.*?>(.*?)<\/a>.*?<span.*?class="teaser-price".*?>(.*?)<\/span>.*?<div.*?class="more_info_region".*?>(.*?)<\/div>.*?<div.*?class="meta submitted".*?><span.*?content="(.*?)".*?><\/span>.*?<\/div>'

        data = re.findall(pattern, search_data, re.DOTALL)
        
        return [d for d in data if not d[0].lower().startswith(('куплю', 'обменяю'))]
    return [0,0,0,0]

data = parsing("https://irza.ru/russia/guns_sale?ysclid=lbymq1j946340256400")
# Последующие страницы
next_list = [[]]
next_list.extend( parsing(f"https://irza.ru/russia/guns_sale?page={i}") for i in range(1, 6))

for x in next_list:
    data.extend(x if isinstance(x, list) else [x] )

# установить максимальное количество отображаемых строк и столбцов
# pd.options.display.max_rows = None
# pd.options.display.max_columns = None
# создаем DataFrame из списка

#print(data)
df = pd.DataFrame(data, columns=['Название', 'Цена', 'Место размещения', 'Дата'])

# loop through each row in the DataFrame
for i, row in df.iterrows():
    # check if the price ends with "т.р."
    if str(row['Цена']).endswith('т.р.'):
        # replace the "т.р." suffix with "000"
        price = str(row['Цена']).replace('т.р.', '000 руб.')
        # update the value in the DataFrame
        df.at[i, 'Цена'] = price


print(getcourse.parsing('https://cbr.ru/'))

print(df)
# записать DataFrame в файл Excel
df.to_excel('dataframe_allData.xlsx', index=False)

print(type(df['Цена'][0]))

# конвертируем столбец "Цена" в числовой формат
df['Цена'] = df['Цена'].str.replace(' руб.', '', regex=True).str.replace(' ', '').astype(int)

# создаем маску, которая будет возвращать True для значений, которые больше 20 000 и меньше 50 000
mask = (df['Цена'] > 20000) & (df['Цена'] < 50000)

# фильтруем DataFrame, используя маску
filtered_df = df[mask]

print(filtered_df)

# записать filter DataFrame в файл Excel
filtered_df.to_excel('dataframe_filteredData.xlsx', index=False)

