import urllib.request
import sys
import os
import time


def updateDb():
    maxSec = 24 * 3600
    url = "https://bazaar.abuse.ch/export/txt/sha256/recent/"
    output = "signatures.txt"

    currentTime =  time.time()

    if os.path.exists(output):
        fileTimestamp = os.path.getmtime(output)
        age = (currentTime - fileTimestamp) / 3600

        if age < maxSec:
            sys.exit(0)

    print(f"Arquivo da base de dados \"{output}\" não foi encontrado ou é muito antigo\nBaixando base de dados...")

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
        if os.path.exists(output):
            print(f"Erro ao atualizar base de dados, mantendo o arquivo original:\n{e}")
            sys.exit(0)
        else:
            print(f"Erro ao baixar base de dados: {e}")
            sys.exit(1)

if __name__ == "__main__":
    updateDb()
