import socket
import threading
import time
import os
import json
import subprocess
import configparser
import re

queue = []
queue_lock = threading.Lock()
restart_requested = False
server_socket = None
stop_video = True

def log(msg):
    print(f"{time.strftime('%H:%M:%S')} | {msg}", flush=True)

def get_local_ip():
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
        try:
            s.connect(("8.8.8.8", 80))
            return s.getsockname()[0]
        except:
            return "127.0.0.1"

def on_start(text, sock):
    try:
        msg = {"evento": "TTS_START", "testo": text}
        sock.sendall((json.dumps(msg) + "\n").encode())
    except Exception as e:
        log(f"Errore in on_start: {e}")

def on_end(text, completed=True, sock=None):
    try:
        msg = {"evento": "TTS_END" if completed else "TTS_STOP", "testo": text}
        sock.sendall((json.dumps(msg) + "\n").encode())
    except Exception as e:
        log(f"Errore in on_end: {e}")

def start_espeak(text, rate="0", sock=None):
    on_start(text, sock)

    # 🔧 Pulizia di tutte le occorrenze di "tts$$"
    cleaned_text = text.replace("tts$$", "").strip()
    cleaned_text = re.sub(r"\s{2,}", " ", cleaned_text)  # Rimuove spazi multipli

    cleaned_text = re.sub(r"\bspeaky\b", "spichi", cleaned_text, flags=re.IGNORECASE)

    log(f"🗣️ Avvio TTS: {cleaned_text} (rate={rate})")
    subprocess.run(["spd-say", "-w", "-l", "it", "-r", rate, cleaned_text], env=os.environ)

    on_end(cleaned_text, completed=True, sock=sock)
    log(f"🛑 Fine TTS: {cleaned_text}")

def monitor_tts_queue():
    while True:
        with queue_lock:
            if queue:
                text, rate, sock = queue.pop(0)
                start_espeak(text, rate, sock)
        time.sleep(0.2)

def handle_client(sock, addr, robot, clients, config_vals):
    global stop_video
    log(f"➡️ Connessione da {addr}")
    rate = "0"
    try:
        while True:
            try:
                data = sock.recv(1024).decode().strip()
                if not data:
                    break
                log(f"📩 Messaggio da {addr}: {data}")

                if data.startswith("tts$$"):
                    text = data[5:]  # tutto ciò che viene dopo "tts$$"
                    with queue_lock:
                        queue.append((text.strip(), rate, sock))
                        log(f"TTS aggiunto in coda: {text.strip()}")

                elif data == "ttsstop":
                        subprocess.run(["spd-say", "-C"], env=os.environ)
                        with queue_lock:
                            queue.clear()
                        log("🛑 Interruzione TTS manuale + svuotamento coda")

                elif data.startswith("ttsrate$$"):
                    _, rate = data.split("$$", 1)
                    log(f"🎚️ Modifica rate TTS: {rate}")

                elif data.startswith("ttsvolume$$"):
                    _, val = data.split("$$", 1)
                    subprocess.run(["amixer", "-c", config_vals["cardnum"], "set", config_vals["cardname"], f"{int(val)*10}%"])
                    log(f"🔊 Volume impostato a {val}")

            except socket.timeout:
                continue  # Client inattivo, non disconnettere

    except Exception as e:
        log(f"❌ Errore client {addr}: {e}")
    finally:
        sock.close()
        log(f"⛔ Disconnesso: {addr}")

        

def start_server(robot, clients, config_vals):
    global server_socket, restart_requested
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server_socket.settimeout(1)
    server_socket.bind(("0.0.0.0", 6000))
    server_socket.listen(5)
    log("✅ Server in ascolto sulla porta 6000")

    while not restart_requested:
        try:
            client_sock, addr = server_socket.accept()
            client_sock.settimeout(10)
            threading.Thread(target=handle_client, args=(client_sock, addr, robot, clients, config_vals), daemon=True).start()
        except socket.timeout:
            continue
        except Exception as e:
            log(f"Errore accept: {e}")
            break

    server_socket.close()
    log("🔁 Server TCP chiuso per riavvio")

def discovery_service():
    global restart_requested
    udp_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    udp_sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    udp_sock.bind(("", 5000))
    log("📡 Discovery attivo sulla porta 5000")

    while True:
        msg, client_addr = udp_sock.recvfrom(1024)
        text = msg.decode().strip()
        log(f"🔄 Discovery trigger da {client_addr}: {text}")
        restart_requested = True
        time.sleep(1)
        restart_requested = False
        udp_sock.sendto(b"DISCOVERY_RESPONSE", (client_addr[0], 5001))

def main():
    config = configparser.ConfigParser()
    config.read("config.ini")
    robot = None
    clients = None
    config_vals = None

    threading.Thread(target=monitor_tts_queue, daemon=True).start()
    threading.Thread(target=discovery_service, daemon=True).start()

    while True:
        start_server(robot, clients, config_vals)

if __name__ == "__main__":
    log(f"🌐 Indirizzo IP locale: {get_local_ip()}")
    main()
