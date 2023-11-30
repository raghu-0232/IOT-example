# Import necessary libraries
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

# Function to get sensor data from ESP8266
def get_sensor_data():
    try:
        # Make HTTP GET requests to get temperature and humidity data
        return requests.get(temperature_uri).text, requests.get(humidity_uri).text
    except requests.exceptions.ConnectionError:
        # Handle connection error and retry
        print("Connection error. Retrying...")
        return None, None

# Function to insert data into MySQL database
def insert_into_database(temperature, humidity):
    cursor = None
    connection = None  # Initialize connection outside the try block
    
    while True:
        try:
            # Establish connection to MySQL
            connection = mysql.connector.connect(**db_config)
            cursor = connection.cursor()

            # Execute SQL query to insert temperature and humidity into the table
            cursor.execute("INSERT INTO sensor_data (temperature, humidity) VALUES (%s, %s)",
                           (float(temperature), float(humidity)))
            
            # Commit changes to the database
            connection.commit()
            
            print("Data inserted into MySQL database.")
            break  # Break out of the loop if successful

        except mysql.connector.Error as e:
            print(f"Error: {e}")

            # Handle specific database connection errors
            if e.errno == mysql.connector.errorcode.ER_ACCESS_DENIED_ERROR:
                print("Database connection error: Access denied. Check username and password.")
            elif e.errno == mysql.connector.errorcode.ER_BAD_DB_ERROR:
                print("Database connection error: Database does not exist.")
            else:
                print("Database connection error. Retrying...")
            
            time.sleep(10)  # Wait for 10 seconds before retrying

        finally:
            # Close cursor and connection
            if cursor:
                cursor.close()
            if connection and connection.is_connected():
                connection.close()

# Main script
if __name__ == "__main__":
    try:
        while True:
            # Get sensor data
            temperature, humidity = get_sensor_data()

            if temperature is not None and humidity is not None:
                # Print sensor data
                print(f"Temperature: {temperature} °C, Humidity: {humidity} %")
                
                # Insert data into MySQL database
                insert_into_database(temperature, humidity)

            # Wait for 10 seconds before the next reading
            time.sleep(10)
    except KeyboardInterrupt:
        # Handle keyboard interruption
        print("Script terminated by user.")
