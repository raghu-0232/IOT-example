<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Temperature and Humidity</title>
</head>
<body>
  <h1>Temperature and Humidity Data</h1>
  <table border="1">
    <tr>
      <th>Temperature (°C)</th>
      <th>Humidity (%)</th>
    </tr>
    <tr>
      <td id="temperature">Loading...</td>
      <td id="humidity">Loading...</td>
    </tr>
  </table>

  <script>
    async function fetchData() {
      try {
        const response = await fetch('/api/data');
        const data = await response.json();

        // Update the table with the fetched data
        document.getElementById('temperature').textContent = data.temp;
        document.getElementById('humidity').textContent = data.hum;
      } catch (error) {
        console.error('Error fetching data:', error);
      }
    }

    // Fetch data initially and then every 10 seconds
    fetchData();
    setInterval(fetchData, 10000);
  </script>
</body>
</html>
