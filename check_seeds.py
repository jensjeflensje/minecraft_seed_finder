import subprocess
import threading

START_SEED = 4000
TOTAL = 2000
THREADS = 10
PER_THREAD = TOTAL / THREADS

MAX_SIZE = 2500
STEP = 16

OUT_FILE = "./seeds.txt"

def create_thread(start, end):
    process = subprocess.Popen(
        [f"./seed_find", str(start), str(end), str(MAX_SIZE), str(STEP)],
        stdout=subprocess.PIPE,
    )
    while True:
        line = process.stdout.readline().decode("utf-8")
        if not line: break
        if line.startswith("FOUND"):
            seed_number = line.strip().split(" ")[-1]
            print(f"Writing {seed_number}", flush=True)
            seed_file = open(OUT_FILE, "a")
            seed_file.write(seed_number + "\n")
            seed_file.close()

for i in range(THREADS):
    start = START_SEED + int(i * PER_THREAD)
    end = int(start + PER_THREAD)

    threading.Thread(target=create_thread, args=(start, end)).start()
    print(f"Started thread {i}")

print("Running...")

    
