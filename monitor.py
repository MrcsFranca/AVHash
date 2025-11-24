import sys
import time 
import os
import subprocess
from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler

PATH = os.path.expanduser("~/Downloads")
EXEC = "./AVHash"

class watchDownloads(FileSystemEventHandler):
    def on_created(self, event):
        if event.is_directory:
            return
        fileName = event.src_path

        ignoredExtensions = ('.tmp', '.crdownload', '.part')
        if fileName.endswith(ignoredExtensions):
            return

        print(f"[AVISO] Novo arquivo detectado: {fileName}")
        self.scan(fileName)

    def on_moved(self, event):
        if event.is_directory:
            return

        fileName = event.dest_path
        print(f"Download de arquivo finalizado detectado: {fileName}")
        self.scan(fileName)

    def scan(self, fileName):
        time.sleep(1)

        print(f"Analisando o arquivo: {fileName}")
        try:
            subprocess.run([EXEC, fileName], check=False)
        except FileNotFoundError:
            print(f"Erro -> executável {EXEC} não encontrado")

if __name__ == "__main__":
    if not os.path.exists(PATH):
        print(f"A pasta {PATH} não existe")
        sys.exit(1)

    if not os.path.exists(EXEC):
        print(f"O arquivo {EXEC} não foi encontrado")
        sys.exit(1)

    eventHandler = watchDownloads()

    observer = Observer()
    observer.schedule(eventHandler, PATH, recursive=False)

    print(f"Monitorando a pasta {PATH}")
    print("Pressione Ctrl+C para parar")
    print("----------------------------\n")

    observer.start()

    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        observer.stop()

    observer.join()
