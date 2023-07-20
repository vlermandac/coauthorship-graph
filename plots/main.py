import pandas as pd
# import plot
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

df_article_1 = pd.read_csv("./../results/article/221918_08_07_2023/table1.csv")
df_article_2 = pd.read_csv("./../results/article/221918_08_07_2023/table2.csv")

df_inproceedings_1 = pd.read_csv("./../results/inproceedings/221918_08_07_2023/table1.csv")
df_inproceedings_2 = pd.read_csv("./../results/inproceedings/221918_08_07_2023/table2.csv")

# PRE-PROCESS
dataframes = []
for i, df in enumerate([df_article_1, df_article_2, df_inproceedings_1, df_inproceedings_2]):
    temp = df[(df['year'] >= 1940) & (df['year'] <= 2020)].copy()
    temp['year'] = temp['year'].astype(int)
    temp['year_bin'] = (temp['year'] // 10) * 10
    dataframes.append(temp)


fig, axes = plt.subplots(nrows=2, ncols=2, figsize=(14, 10))
axes = axes.ravel()  # Flatten the 2D array to 1D for easy iteration
# BOXPLOT PROCESS
for i,df in enumerate(dataframes):
    unrolled_data = [(year_bin, col) for _, row in df.iterrows() 
                     for year_bin in [row['year_bin']]  # Need to put this in a list to use in the inner loop
                     for col in df.columns 
                     if col not in ['year', 'year_bin'] 
                     for _ in range(row[col])]
    unrolled_data = np.array(unrolled_data)
        
    # Convert the array to a DataFrame for easier manipulation
    unrolled_df = pd.DataFrame(unrolled_data, columns=['YearBin', 'Value'])
    unrolled_df['Value'] = unrolled_df['Value'].astype(int)
    
    # Now unrolled_df has all the unrolled data and it can be plotted
    sns.boxplot(x='YearBin', y='Value', data=unrolled_df, orient='v', ax=axes[i])
    
plt.tight_layout()  # Ensure the subplots do not overlap
plt.show()                
