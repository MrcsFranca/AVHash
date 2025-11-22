import urllib.request
import sys
import os

def updateDb():
    url = "https://bazaar.abuse.ch/export/txt/sha256/recent/"
    output = "signatures.txt"

    if os.path.exists(output):
        sys.exit(0)

    print(f"Arquivo da base de dados \"{output}\" não foi encontrado\nBaixando base de dados...")

    try:
        with urllib.request.urlopen(url) as response:
            data = response.read().decode('utf-8')

        lines = []
        lineNumber = 0

        for line in data.splitlines():
            line = line.strip()

            if not line or line.startswith('#'):
                continue

            lines.append(line)
            lineNumber += 1

        with open(output, "w") as file:
            for hash in lines:
                file.write(hash + "\n")

        print(f"{lineNumber} linhas salvo em {output}")
        sys.exit(0)

    except Exception as e:
        print(f"Erro ao atualizar base de dados:\n{e}")
        sys.exit(1)

if __name__ == "__main__":
    updateDb()
