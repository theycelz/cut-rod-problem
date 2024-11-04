import os
import subprocess

def run_make():
    print("Executando make...")
    subprocess.run(["make"], cwd="src/core")

def run_executable():
    print("Executando o programa C...")
    subprocess.run(["./rod_cutting"], cwd="src/core")

def run_analysis():
    print("Executando análise de resultados...")
    subprocess.run(["python", "src/utils/analysis_stats.py"])

def run_visualization():
    print("Gerando visualizações dos dados...")
    subprocess.run(["python", "src/utils/data_plot.py"])

def main():
    executable_path = os.path.join("core", "src/core/rod_cutting")
    data_path = os.path.join("src/data", "resultados.txt")

    # Verifica se o executável existe
    if not os.path.exists(executable_path):
        run_make()

    # Executa o programa C
    run_executable()

    # Verifica se o arquivo de resultados foi gerado
    if os.path.exists(data_path):
        run_analysis()
        run_visualization()
    else:
        print("Erro: O arquivo 'resultados.txt' não foi encontrado.")

if __name__ == "__main__":
    main()