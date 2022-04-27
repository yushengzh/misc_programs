import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.metrics import roc_curve, auc
import warnings
warnings.filterwarnings("ignore")


## 读取资料
def read_dat(filePath, column):
    f = open(filePath, encoding='unicode_escape')
    datlist = []
    for line in f:
        l = line.strip().split('::')
        datlist.append(l)
    return pd.DataFrame(datlist, columns=column)

## 把数据资料分成两部分：训练集90% 测试集10%
def split_Data(df_data):
    mask = np.random.rand(len(df_data)) < .9
    train_data = df_data[mask]
    test_data = df_data[~mask]
    return train_data, test_data   


## 评价>3的用户-电影_DataFrame
def users_prefer_movies(ratings):
    ratings['prefer'] = ratings['Rating'] > '3'
    ratings['prefer'] = ratings['prefer'].astype(int)
    user_movie = pd.DataFrame(ratings, columns=['UserID', 'MovieID', 'prefer'])
    user_movie_prefer = user_movie[user_movie['prefer'] == True]
    return user_movie_prefer



movies_path = ".\\movies.dat"
users_path = "users.dat"
ratings_path = 'ratings.dat'
movies_column = ['MovieID', 'Title', 'Genres']
users_column = ['UserID', 'Gender', 'Age', 'Occupation', 'Zip-code']
ratings_column = ['UserID', 'MovieID', 'Rating', 'Timestamp']
df_movies = read_dat(movies_path, movies_column)
df_users = read_dat(users_path, users_column)
df_ratings = read_dat(ratings_path, ratings_column)
print(df_movies)
