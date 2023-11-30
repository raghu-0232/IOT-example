import requests
from datetime import datetime
import time
import mysql.connector

# MySQL database configuration
db_config = {'host': 'localhost', 'user': 'root', 'password': '123456', 'database': 'esp8266'}

# ESP8266 IP address
esp_ip = "192.168.0.193"

# URIs for temperature and humidity
temperature_uri = f"http://{esp_ip}/temperature"
humidity_uri = f"http://{esp_ip}/humidity"

def get_sensor_data():
    try:
        return requests.get(temperature_uri).text, requests.get(humidity_uri).text
    except requests.exceptions.ConnectionError:
        print("Connection error. Retrying...")
        return None, None

def insert_into_database(temperature, humidity):
    connection = mysql.connector.connect(**db_config)
    cursor = connection.cursor()

    try:
        cursor.execute("INSERT INTO sensor_data (temperature, humidity) VALUES (%s, %s)",
                       (float(temperature), float(humidity)))
        connection.commit()
        print("Data inserted into MySQL database.")
    except Exception as e:
        print(f"Error: {e}")
        connection.rollback()
    finally:
        cursor.close()
        connection.close()

if __name__ == "__main__":
    try:
        while True:
            temperature, humidity = get_sensor_data()

            if temperature is not None and humidity is not None:
                print(f"Temperature: {temperature} °C, Humidity: {humidity} %")
                insert_into_database(temperature, humidity)

            time.sleep(10)
    except KeyboardInterrupt:
        print("Script terminated by user.")
