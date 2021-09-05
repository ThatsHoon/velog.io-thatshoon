#!/usr/bin/env python
# coding: utf-8

# In[229]:


import os
from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.chrome.options import Options
from selenium.common.exceptions import *

import time
import json
import pandas as pd
import numpy as np

URL = "https://lostark.game.onstove.com/Market"

options = Options()
options.add_argument('--start-fullscreen')

driver = webdriver.Chrome(chrome_options=options)
driver.implicitly_wait(5)

driver.set_window_size(1920, 1080)
driver.get(url=URL)

goto = driver.find_element_by_xpath('//*[@id="user_id"]')
goto.send_keys("hunje159@naver.com")

goto = driver.find_element_by_xpath('//*[@id="user_pwd"]')
goto.send_keys("hj52170236^^")

goto = driver.find_element_by_xpath('//*[@id="idLogin"]/div[3]/button')
goto.send_keys(Keys.RETURN)

goto = driver.find_element_by_class_name('button--deal-submit')
goto.send_keys(Keys.RETURN)
driver.execute_script("document.body.style.zoom='75%'")
time.sleep(5)
driver.find_element_by_xpath('//*[@id="itemList"]/thead/tr/th[1]/a').send_keys(Keys.RETURN)
time.sleep(5)

data = pd.read_json("data.json")

try :
    for j in range(510) :
        for i in range(1,11) :
            아이템명 = driver.find_element_by_xpath('//*[@id="tbodyItemList"]/tr[%d]/td[1]/div/span[2]' % i).text
            전일평균거래가 = driver.find_element_by_xpath('//*[@id="tbodyItemList"]/tr[%d]/td[2]/div/em' % i).text
            최저가 = driver.find_element_by_xpath('//*[@id="tbodyItemList"]/tr[%d]/td[4]/div/em' % i).text
            data.loc[아이템명, 어제날짜] = 전일평균거래가
            data.loc[아이템명, "최저가"] = 최저가

        페이지위치 = int(driver.find_element_by_xpath('//*[@id="marketList"]/div[2]/em').text)%10
        if 페이지위치 == 0 : 
            다음10페이지 = driver.find_element_by_css_selector("a.pagination__next")
            다음10페이지.send_keys(Keys.RETURN)
        else :
            다음페이지 = driver.find_element_by_xpath('//*[@id="marketList"]/div[2]/a[%d]' % (페이지위치+2))
            다음페이지.send_keys(Keys.RETURN)
        time.sleep(2)
except NoSuchElementException: 
    data.to_json("data.json")
data.to_json("data.json")

