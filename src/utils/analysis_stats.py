import os
from typing import List, Dict
import pandas as pd

def parse_file_content(content: str) -> pd.DataFrame:
    return pd.DataFrame([
        {
            'n': int(line.split()[0]),
            'vDP': float(line.split()[1]),
            'tDP': float(line.split()[2]),
            'vGreedy': float(line.split()[3]),
            'tGreedy': float(line.split()[4]),
            'efficiency': float(line.split()[5].strip('%'))/100
        }
        for line in content.strip().split('\n')[2:]
        if not line.startswith('--')
    ])

def calculate_time_metrics(means: pd.DataFrame) -> Dict:
    return {
        'dp_mean': means['tDP'].mean(),
        'dp_growth': (means['tDP'].iloc[-1] - means['tDP'].iloc[0]) / means['tDP'].iloc[0],
        'greedy_mean': means['tGreedy'].mean()
    }

def calculate_range_stats(data: pd.DataFrame) -> Dict:
    return {
        'mean_efficiency': data['efficiency'].mean(),
        'std_efficiency': data['efficiency'].std(),
        'mean_tDP': data['tDP'].mean(),
        'mean_tGreedy': data['tGreedy'].mean()
    }

def analyze_results(dataframes: List[pd.DataFrame]) -> Dict:
    all_results = pd.concat(dataframes)
    grouped = all_results.groupby('n')
    means = grouped.mean()
    std_devs = grouped.std()
    
    return {
        'execution_time': calculate_time_metrics(means),
        'std_dev': {'dp': std_devs['vDP'].mean(), 'greedy': std_devs['vGreedy'].mean()},
        'worst_cases': all_results.nsmallest(5, 'efficiency')[['n', 'efficiency']].to_dict('records'),
        'range_stats': {
            f"{'n>=15000' if n >= 15000 else 'n<15000'}": calculate_range_stats(data)
            for n, data in all_results.groupby(all_results['n'].ge(15000))
        },
        'inflection_points': means['efficiency'].diff().abs().nlargest(3).index.tolist()
    }

def format_analysis(analysis: Dict) -> str:
    sections = [
        "=== ANÁLISE DE PERFORMANCE ===",
        "\n1. TEMPO DE EXECUÇÃO",
        f"Programação Dinâmica: {analysis['execution_time']['dp_mean']:.6f}",
        f"Crescimento: {analysis['execution_time']['dp_growth']:.2%}",
        f"Algoritmo Guloso: {analysis['execution_time']['greedy_mean']:.6f}",
        "\n2. DESVIO PADRÃO",
        f"Programação Dinâmica: {analysis['std_dev']['dp']:.2f}",
        f"Algoritmo Guloso: {analysis['std_dev']['greedy']:.2f}",
        "\n3. CASOS DE DIVERGÊNCIA",
        *[f"n={case['n']}: {case['efficiency']:.2%}" for case in analysis['worst_cases']],
        "\n4. ANÁLISE POR FAIXA",
        *[f"{range_name}:\n" + \
          f"Eficiência: {stats['mean_efficiency']:.2%}\n" + \
          f"Desvio: {stats['std_efficiency']:.4f}\n" + \
          f"Tempo DP: {stats['mean_tDP']:.4f}\n" + \
          f"Tempo Guloso: {stats['mean_tGreedy']:.4f}"
          for range_name, stats in analysis['range_stats'].items()],
        "\n5. PONTOS DE INFLEXÃO",
        *[f"n={n}" for n in analysis['inflection_points']]
    ]
    return "\n".join(sections)

def main() -> None:
    script_dir = os.path.dirname(os.path.abspath(__file__))
    data_dir = os.path.join(script_dir, '..', '..', 'data')
    
    results = []
    try:
        results.append(parse_file_content(open(os.path.join(data_dir, 'resultados.txt')).read()))
    except FileNotFoundError:
        results = [
            parse_file_content(open(os.path.join(data_dir, f'resultados{i}.txt')).read())
            for i in range(1, 4)
        ]
    
    analysis = analyze_results(results)
    formatted_analysis = format_analysis(analysis)
    
    results_dir = os.path.join(script_dir, '..', '..', 'results')
    os.makedirs(results_dir, exist_ok=True)
    filepath = os.path.join(results_dir, 'analysis_results.txt')
    
    with open(filepath, 'w') as f:
        f.write(formatted_analysis)

if __name__ == "__main__":
    main()