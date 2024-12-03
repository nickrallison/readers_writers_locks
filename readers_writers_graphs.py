import re
import pandas as pd
import matplotlib.pyplot as plt

# Multiline string containing the data
data = """
Readers-Writers Solution 1 (time in seconds)
Writers  AVG reader TAT  AVG writer TAT  AVG TAT
0        0.161316        N/A             0.161316
1        0.127671        0.158353        0.130460
2        0.133194        0.153255        0.136537
3        0.101917        0.143732        0.111566
4        0.125872        0.163522        0.136629
5        0.124202        0.176509        0.141638
6        0.134949        0.179736        0.151745
7        0.136720        0.194863        0.160661
8        0.117966        0.185589        0.148021
9        0.129376        0.201107        0.163354
10       0.141836        0.238081        0.189959
Readers-Writers Solution 2 (time in seconds)
Writers  AVG reader TAT  AVG writer TAT  AVG TAT
0        0.076169        N/A             0.076169
1        0.076814        0.000466        0.069873
2        0.092881        0.014723        0.079854
3        0.090566        0.021136        0.074544
4        0.113186        0.039908        0.092250
5        0.114869        0.047958        0.092566
6        0.179181        0.094719        0.147508
7        0.184950        0.111549        0.154726
8        0.189189        0.121279        0.159007
9        0.200049        0.129584        0.166671
10       0.222391        0.145754        0.184072
Readers-Writers Solution 3 (time in seconds)
Writers  AVG reader TAT  AVG writer TAT  AVG TAT
0        0.088868        N/A             0.088868
1        0.071522        0.076622        0.071985
2        0.081491        0.086596        0.082342
3        0.089835        0.093943        0.090783
4        0.091233        0.099513        0.093598
5        0.105165        0.110519        0.106949
6        0.113716        0.119175        0.115763
7        0.120687        0.128008        0.123702
8        0.130149        0.135696        0.132614
9        0.133273        0.140728        0.136804
10       0.136118        0.145511        0.140814
"""

# Split the data into sections
sections = data.strip().split('Readers-Writers Solution')
for i, section in enumerate(sections):
    sections[i] = "Readers-Writers Solution" + sections[i]
sections = sections[1:]

# Process each section
for section in sections:
    title = re.search(r'Readers-Writers Solution \d+', section).group()
    col_titles = ["Writers", "AVG reader TAT", "AVG writer TAT", "AVG TAT"]
    data_lines = section.split('\n')[2:]
    data_lines = [line for line in data_lines if line]

    # Create a DataFrame
    df = pd.DataFrame([line.split() for line in data_lines], columns=col_titles)
    df['Writers'] = df['Writers'].astype(int)
    df['AVG reader TAT'] = pd.to_numeric(df['AVG reader TAT'], errors='coerce')
    df['AVG writer TAT'] = pd.to_numeric(df['AVG writer TAT'], errors='coerce')
    df['AVG TAT'] = pd.to_numeric(df['AVG TAT'], errors='coerce')

    # Plotting
    plt.figure(figsize=(10, 6))
    plt.scatter(df['Writers'], df['AVG reader TAT'], label='AVG reader TAT', marker='o')
    plt.scatter(df['Writers'], df['AVG writer TAT'], label='AVG writer TAT', marker='x')
    plt.scatter(df['Writers'], df['AVG TAT'], label='AVG TAT', marker='s')

    plt.title(title)
    plt.xlabel('Writers')
    plt.ylabel('Time (seconds)')
    plt.legend()
    plt.grid(True)
    plt.tight_layout()

    # Save the plot as a PNG file
    plt.savefig(f'{title}.png')
    plt.show()