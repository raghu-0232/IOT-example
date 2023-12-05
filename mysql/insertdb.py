import json
import mysql.connector
import paho.mqtt.client as mqtt
from datetime import datetime
import time

# MySQL database configuration
db_config = {'host': 'localhost', 'user': 'root', 'password': 'Raghu123@', 'database': 'esp'}

# MQTT configuration
mqtt_broker = "localhost"  # Update this with your MQTT broker address
mqtt_topic = "test"  # Update this with your MQTT topic

# Function to insert data into MySQL database
def insert_into_database(temperature, humidity):
    cursor = None
    connection = None
    
    try:
        # Establish connection to MySQL
        connection = mysql.connector.connect(**db_config)
        cursor = connection.cursor()

        # Execute SQL query to insert temperature and humidity into the table
        cursor.execute("INSERT INTO sensor_data (temp, hum, timestamp) VALUES (%s, %s, %s)",
                       (float(temperature), float(humidity), datetime.now()))
        
        # Commit changes to the database
        connection.commit()
        
        print("Data inserted into MySQL database.")

    except mysql.connector.Error as e:
        print(f"Error: {e}")

    finally:
        # Close cursor and connection
        if cursor:
            cursor.close()
        if connection and connection.is_connected():
            connection.close()

# Callback function when a message is received from the MQTT broker
def on_message(client, userdata, msg):
    try:
        # Decode the JSON message payload
        payload = json.loads(msg.payload.decode())
        
        # Extract temperature and humidity from the payload
        temperature = payload.get('temperature')
        humidity = payload.get('humidity')

        if temperature is not None and humidity is not None:
            # Print sensor data
            print(f"Temperature: {temperature} °C, Humidity: {humidity} %")
            
            # Insert data into MySQL database
            insert_into_database(temperature, humidity)

    except Exception as e:
        print(f"Error processing MQTT message: {e}")

# Main script
if __name__ == "__main__":
    try:
        # Initialize MQTT client
        client = mqtt.Client()
        client.on_message = on_message

        # Connect to MQTT broker
        client.connect(mqtt_broker, 1883, 60)
        client.subscribe(mqtt_topic)

        # Start the MQTT client loop
        client.loop_start()

        # Run indefinitely
        while True:
            time.sleep(1)

    except KeyboardInterrupt:
        # Handle keyboard interruption
        print("Script terminated by user.")
        client.disconnect()
