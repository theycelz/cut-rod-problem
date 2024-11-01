import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

def carregar_dados(arquivo):
    return pd.read_csv(arquivo, sep="\s+", engine='python')  
