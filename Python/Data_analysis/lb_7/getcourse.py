from bs4 import BeautifulSoup
import requests
import re
import fake_useragent
import pandas as pd

# Делаем запросы с разными User-Agent
user = fake_useragent.UserAgent().random 
# Заголовки
headers = {'User-Agent': user}

def parsing(url = 'https://cbr.ru/'):
    # Создаем сессию для запроса 
    request_session = requests.Session()
    # Делаем запрос
    request = request_session.get(url, headers=headers)
    # Проверяем статус запроса
    if request.status_code == 200:
        # Создаем объект BeautifulSoup для парсинга
        soup = BeautifulSoup(request.content,'lxml') 
        
        search_data = str(soup.find('div',class_ = 'col-md-2 col-xs-9 _right mono-num'))
        pattern = r'\d+,\d+'

        result = str(re.findall(pattern, search_data)[0]).replace(',','.')

        return float(result)
