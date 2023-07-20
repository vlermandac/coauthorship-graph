import matplotlib.pyplot as plt

class bar_plot:
    def __init__(self, df, years):
        self.df = df
        self.years = years

    def create_bar_plot(self, title):
        self.df['Average'] = self.df.drop('year', axis=1).mean(axis=1)
        plt.figure(figsize=(10, 6))
        plt.bar(self.years[-30:], self.df['Average'][-30:])
        plt.xlabel('Years')
        plt.ylabel('Row Average')
        plt.title(title)
        plt.show()

