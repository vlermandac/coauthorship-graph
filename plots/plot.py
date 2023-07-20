import pandas as pd
from classes.bar import bar_plot


def display_plots():
    bar_plot_creator_1 = bar_plot(df_article_1, years)
    bar_plot_creator_1.create_bar_plot("Cantidad de Co-autorias en publicaciones (article) entre Pares de Autores (Avg per year)")

    bar_plot_creator_2 = bar_plot(df_article_2, years)
    bar_plot_creator_2.create_bar_plot("Cantidad de Co-autorias en publicaciones (inproceedings) entre Pares de Autores (Avg per year)")

    bar_plot_creator_3 = bar_plot(df_inproceedings_1, years)
    bar_plot_creator_3.create_bar_plot("Cantidad de autores por publicación (article) (Avg per year)")

    bar_plot_creator_4 = bar_plot(df_inproceedings_2, years)
    bar_plot_creator_4.create_bar_plot("Cantidad de autores por publicación (inproceedings) (Avg per year)")
