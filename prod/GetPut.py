import requests
import csv
from datetime import datetime
import time
import mysql.connector

# MySQL database configuration
db_config = {
    'host': 'localhost',     # e.g., 'localhost'
    'user': 'root',     # e.g., 'raghu'
    'password': '123456',
    'database': 'esp8266',  # e.g., 'your_esp8266_database'
}

# ESP8266 IP address
esp_ip = "192.168.0.193"

# URIs for temperature and humidity
temperature_uri = f"http://{esp_ip}/temperature"
humidity_uri = f"http://{esp_ip}/humidity"

# CSV file name
csv_file = "temperature_humidity_data.csv"

def get_sensor_data():
    try:
        # Make HTTP GET requests to ESP8266
        temperature_response = requests.get(temperature_uri)
        humidity_response = requests.get(humidity_uri)

        # Return temperature and humidity as a tuple
        return temperature_response.text, humidity_response.text
    except requests.RequestException as e:
        print(f"Error: {e}")
        return None, None

def save_to_csv(data):
    # Get current timestamp
    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

    # Append data to CSV file
    with open(csv_file, mode='a', newline='') as file:
        writer = csv.writer(file)
        writer.writerow([timestamp, *data])

def insert_into_database(temperature, humidity):
    # Connect to MySQL
    connection = mysql.connector.connect(**db_config)
    cursor = connection.cursor()

    try:
        # SQL query to insert data into the table
        query = "INSERT INTO sensor_data (temperature, humidity) VALUES (%s, %s)"
        data = (float(temperature) if temperature else None, float(humidity) if humidity else None)

        # Execute the query
        cursor.execute(query, data)

        # Commit changes
        connection.commit()
        print("Data inserted into MySQL database.")
    except Exception as e:
        print(f"Error: {e}")
        # Rollback in case of an error
        connection.rollback()
    finally:
        # Close the cursor and connection
        cursor.close()
        connection.close()

if __name__ == "__main__":
    try:
        while True:
            # Get sensor data
            temperature, humidity = get_sensor_data()

            # Print the data (optional)
            if temperature is not None and humidity is not None:
                print(f"Temperature: {temperature} °C, Humidity: {humidity} %")
            else:
                print("Error: Failed to get sensor data.")

            # Save data to CSV file
            save_to_csv([temperature, humidity])

            # Insert data into MySQL database
            insert_into_database(temperature, humidity)

            # Wait for 10 seconds before the next reading
            time.sleep(10)
    except KeyboardInterrupt:
        print("Script terminated by user.")
